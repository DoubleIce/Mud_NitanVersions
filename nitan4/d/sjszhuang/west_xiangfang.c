//Cracked by Roath
// group bwdh/room west xiangfang
// Apache 09/27/98

#include <ansi.h>
inherit ROOM;
#include "entrance.h"
#include "xiangfang.h"
#define BOARD "/clone/board/bwboard"

void death_stage(object ob, int stage);
void setup_weishi(object weishi,object ob);

void create() {
	 set("short", "西厢房");
	 set("long", @LONG
这里是西厢房。比武较量的选手在这里组队准备入场。
厢房里面放者几个兵器架(jia)，摆满了兵器。
LONG
	 );

	 set("no_fight",1);
	 set("no_death",1);
	 set("no_magic",1);

	 set("exits", ([
		  "up"    : __DIR__"wizroom",
//        "west" : __DIR__"kantai_w1",
	 ]));
	 create_xiangfang();
	 setup();
}

void init() {
	 init_xiangfang();
	 go_xiangfang();
	 call_out( "death_stage", 90, previous_object(), 0 );
}


void death_stage(object ob, int stage)
{
	object weishi,*weishis;
	int nMyWeiShi=0,nOtherWeiShi=0;
	int i;
	object board;

	if( !ob || !objectp(ob) || !userp(ob) ) return;

	tell_object(ob, HIW "一股阴冷的浓雾突然出现，很快地包围了你。\n\n" NOR );
	//if( !ob->query("sjsz/team_name") ) ob->set("sjsz/team_name",HIR"火龙队"NOR);
	ob->set("sjsz/fighting",1);
	ob->set("sjsz/red",1);
	ob->delete("sjsz/white");

	if( !ob->query("sjsz/team_name") )
	{
		board =  find_object(BOARD);
		if (!objectp(board)) {
				  board = load_object(BOARD);
				  if (!objectp(board))
						return;
		}
		ob->set( "sjsz/team_name",board->query("westname") );
	}

	ob->set_temp("apply/short", ({HIW""+ob->query("sjsz/team_name")+"  "NOR+ob->name()+"("+ob->query("id")+")"}));
	ob->move("/d/sjszhuang/wgate.c");
	message("vision",
					 "你忽然发现前面多了一个人影。\n", environment(ob), ob);

	weishis = filter_array(children(__DIR__"npc/weishi.c"), (: clonep :));

	for( i = 0; i < sizeof(weishis); i++)
	{
		weishi = weishis[i];
		if( weishi->query("sjsz/team_name") == ob->query("sjsz/team_name") )
			nMyWeiShi++;
		else nOtherWeiShi++;
	}

	if( nMyWeiShi > nOtherWeiShi+3 || nMyWeiShi >8  ) return;

	weishi = new (__DIR__"npc/weishi.c");
	if(!weishi)return;

	if(random(4)==1)
		weishi->move(__DIR__"wtang");
	else
		weishi->move(__DIR__"room_01");			

	setup_weishi(weishi,ob);
	message("vision", "你忽然发现前面多了一个人影。\n", environment(weishi), weishi);
}

void setup_weishi(object me,object obj)
{
	mapping skills;
	array names;
	int level,i;
	mixed exp;

	if(!objectp(me) || !objectp(obj) )return;

	exp = atoi(count_sub(obj->query("combat_exp"), 10000000));
	if( exp < 0 ) exp = 1000000;

	me->set("combat_exp", exp );

	level = pow( exp*10.,0.33333 );
	if(level < 100) level = 100;

	if( count_lt(obj->query("combat_exp"), 3000000) )
	{
		level = level/2 + random(level*2/3);
	}
	else if( count_lt(obj->query("combat_exp"), 5000000))
	{
		level = level/2 + random(level/2);
	}
	else if( count_lt(obj->query("combat_exp"), 8000000))
	{
		level = level/2 + random(level/3);
	}
	else if( count_lt(obj->query("combat_exp"), 10000000))
	{
		level = level/2 + random(level/4);
	}
	else
		level = level/2 + random(level/5);

	skills = me->query_skills();
	names = keys(skills);

	for (i=0; i<sizeof(names); i++) {
	  me->set_skill(names[i], level);
	}

	me->set("sjsz/team_name",obj->query("sjsz/team_name"));
	if(count_gt(exp, 80000000))me->set("name","特级武士");
	else if(count_gt(exp, 60000000))me->set("name","一级武士");
	else if(count_gt(exp, 40000000))me->set("name","二级武士");
	else if(count_gt(exp, 20000000))me->set("name","三级武士");
	else if(count_gt(exp, 5000000))me->set("name","四级武士");
	else me->set("name","五级武士");

	me->set_temp("apply/short", ({HIW""+obj->query("sjsz/team_name")+"  "NOR+me->name()+"(wu shi)"}));
}


int do_open(string arg) {
	 if ( !wizardp(this_player()) )
		  return notify_fail("你不是巫师。\n");
	 if (!arg || (arg != "entrance" && arg != "exit") )
		  return notify_fail("你要打开什么？\n");
	 if( arg == "entrance" )
	 {
		 if ( query("exits/east") )
		  return notify_fail("比武场入口已经是打开的。\n");
		 set("exits/east", __DIR__"wgate");
	 }
	 else
	 {
		 if ( query("exits/west") )
			  return notify_fail("比武场入口已经是打开的。\n");
		 set("exits/west", __DIR__"kantai_w1");
	 }
	 message_vision("$N用手指凌空一点，吱地一声，打开了比武场入口。\n", this_player());
	 remove_call_out("close");
	 call_out("close", 60);
	 return 1;
}


int close() {
	 message("vision", "比武场入口慢慢地关上了。\n", this_object());
	 delete("exits/west");
	 delete("exits/east");
	 return 1;
}

int auto_open() {
	 if ( query("exits/east"))
		  return notify_fail("比武场入口已经是打开的。\n");
	 set("exits/east", __DIR__"wgate");
	 message("vision", "“吱～吱～呀～”，比武场入口慢慢打开了。\n", this_object());
	 remove_call_out("close");
	 call_out("close", 60);
	 return 1;
}

int auto_out_open() {
	 if ( query("exits/west") )
		  return notify_fail("比武场入口已经是打开的。\n");
	 set("exits/west", __DIR__"kantai_w1");
	 message("vision", "“吱～吱～呀～”，比武场入口慢慢打开了。\n", this_object());
	 remove_call_out("close");
	 call_out("close", 60);
	 return 1;
}


int valid_leave(object player, string dir) {
	 if (!wizardp(player) && dir == "up")
		  return notify_fail("此间主人并没有邀请你去那里！\n");
	 return ::valid_leave(player, dir);
}
