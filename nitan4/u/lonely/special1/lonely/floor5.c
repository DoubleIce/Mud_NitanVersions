// 自由女神像第五层

#include <ansi.h> 
inherit ROOM;

void create()
{
	set("short", "自由女神像顶层");
	set("long", @LONG
这里是自由女神像的顶层。这里可以俯瞰到整个纽约港。
据说当年一名来自中国名为华英雄的侠客经常在此处纵身跳
下，籍此练就了一身绝世轻功。你也不妨试试(jump)。墙上
还有块突出的砖头,不知去(push zhuan)一下会怎样。
LONG );
	set("exits", ([		
              "down"        : __DIR__"floor4",
	]));
	set("item_desc",([		
              "zhuan"	: "一块突出的砖头，似乎有点古怪。不知道"
                             "(push)一下会怎样。\n",	
	]));
       set("no_fight",1);
       set("no_sleep_room",1); 
       set("no_ride",1);       		
	setup();	
}

void init()
{	
	add_action("do_jump", "jump"); 
       add_action("do_push", "push");             
}

int do_push(string arg)
{
        object room, me;

        me = this_player();

        if (! arg || arg != "zhuan" )
        {
		write("你要按什么？\n");
              return 1;        
        }
        message_sort(HIY"\n$N走到墙边，用力按了一下突出的砖块。"
                     "\n" NOR, me);

        if (! me->query("special_skill/lonely") )
        {
           message_sort(HIY"\n但是$N怎么也按不动这砖。\n" NOR);
           return 1;        
        }

        message_sort(HIY"\n突然墙壁一阵颤动，边上露出一个大洞，\n"
                     "从这里分明通向一个暗室。"
                     "\n\n" NOR, me);
        set("exits/enter", __DIR__"anshi");

        if (room = find_object(__DIR__"anshi"))
        {
        	room->set("exits/out", __FILE__);
           	message("vision", HIY "\n墙壁忽然发出轧轧的声音，"
                        "露出一个向外的通道。\n" NOR, room );
        }
        remove_call_out("close_andao");
        call_out("close_andao", 5);
        return 1;
}

void close_andao()
{
    	object room;
        int i;

        if (! query("exits/enter")) return;
    		message("vision", HIY "\n只听乒地一声响，砖块自动"
                        "移回原处。暗道也随之消失了。\n" NOR, this_object());

    	if (room = find_object(__DIR__"anshi"))
    	{
              room->delete("exits/enter");
        	message("vision", HIY "\n只听乒地一声响，向外的暗道"
                        "口自动严严实实地关了起来。\n" NOR, room);
    	}
    	delete("exits/enter");
}




int do_jump()
{
        object me;

        int i, ging_cost, qi_cost;

        me = this_player();
        me->start_busy(5);
        i = (int)me->query_skill("dodge", 1) + random(5);

        ging_cost = 300 / (int)me->query("int");
        qi_cost = 200 / (int)me->query("int");

        if (((int)me->query("jing") < ging_cost) ||
            ((int)me->query("qi") < qi_cost))
                i = 0;

        message_vision("$N一个纵身，跳了下去。\n", me);
        me->move(__DIR__"newyork");
	 message_vision("只听『砰』地一声$N从女神像顶跳了下来。\n", me);

        if (i < 30)
		message_vision("$N重重地摔了个嘴啃泥，看来是轻功还不到家。\n", me);
	else
        {
		message_vision(WHT"$N已稳稳地站在地上。\n"NOR, me);
		if ( me->query_skill("dodge", 1) < 200)
              {
		     me->improve_skill("dodge", 2 * (10 + random(me->query("dex"))));
		     me->receive_damage("jing", ging_cost);
		     me->receive_damage("qi", qi_cost);
                   tell_object(me,HIC"你的「基本轻功」有了一定的进步！。\n"NOR);
             } else
               tell_object(me,WHT"你的轻功已经没必要再在这里锻炼了。\n"NOR);
	}

        return 1;
}








