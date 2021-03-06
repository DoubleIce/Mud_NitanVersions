#include <ansi.h>
inherit NPC;
inherit BOSS;

int showpower1();
int showpower2();
int combatpower();
int powerup();

void create()
{
	set_name("千年树精", ({ "qiannian shujing", "shujing", "shu jing" }) );
	set("name_color","HIG");
	set("gender", "男性");
	set("age", 2200);
	set("long", 
HIG"这是一个成了精的老榕树，常年餐风饮露！\n\n"NOR);
        
	set("str", 48);
	set("con", 52);
	set("dex", 22);

	set("max_qi", 25000);
	set("max_jing", 25000);
	set("max_gin", 20000);
	set("max_mana",2000);
	set("mana",20000);
	set("max_neili",20000);
	set("neili",20000);
	set("attitude", "aggressive");
	set("limbs", ({ "头部", "身体", "尾巴" }) );
	set("verbs", ({ "bite", "claw" }) );

        set("chat_chance", 5);
        set("chat_msg", ({
        	(: showpower1 :) ,
        	(: showpower2 :)
        }) );    
	
	
	set("chat_chance_combat", 30);
	set("chat_msg_combat", ({
		(: combatpower :),
		
	}) );

	set("combat_exp", 2000000+random(2000000));
        
	set_temp("apply/attack", 20+random(10));
	set_temp("apply/damage",20+random(10));
	set_temp("apply/armor", 20+random(10));
	
	set("bonus", 3000);
	set("killer_reward", killer_reward("shujing"));


	setup();
	carry_object("/clone/money/gold")->set_amount(1);

	// init_npc(this_object(), 6, 13, 0, 100);
// 自动配置NPC属性和技能，第一个参数必须。
// 第一个参数为NPC的OB
// 第二个参数为NPC的门派，1普陀2地府3方寸4月宫5雪山6五庄7龙宫8无底洞其他为基本，不设置为随机门派
// 第三个参数为NPC的技能，按NPC的等级设置(1:50)，缺省或0为不设置
// 第四个参数为NPC的属性和状态等级，按NPC的等级设置，缺省或0为不设置
// 第五个参数为NPC的强度，缺省为100
}

int showpower1()
{
	tell_object(environment(this_object()),HIG"\t林中吹来一阵阴风！差点把你卷走！\n"NOR);
	return 1;
}
int showpower2()
{
	tell_object(environment(this_object()),HIG"\t千年树精突然伸出一根根树枝向你卷了过来！\n"NOR);
	return 1;
}

int combatpower()
{
	message_vision( HIG"\n$N全身发出“咯吱咯吱”的巨响，伸出树枝向你卷了过来！！\n" NOR,this_object());
	remove_call_out("powerup");
	call_out("powerup",random(10)+2);
	return 1;
}

int powerup()
{
	int dam, i , num;
	object *inv;
	message_vision( HIG"\n$N全身晃动．．．．．．整个大地都似乎被掀了起来，你足下一个不稳，差点跌在地上！！！\n",this_object());
        inv = all_inventory(environment(this_object()));
        num = sizeof(inv);
        if (num < 1) num = 1;
        if (num > 5) num = 5;
        dam = 1800 / num;
        for(i=sizeof(inv)-1; i>=0; i--)
        {
        	if( living(inv[i]) && inv[i] != this_object() )
        	{
        		dam = dam - inv[i]->query_combat_level("DF_spells");
        		if(dam <0) dam = 0;
        		inv[i]->receive_wound("qi", dam, this_object());
        		inv[i]->receive_wound("jing", dam/2, this_object());
        		COMBAT_D->report_status(inv[i],1);
        	}
        }
        return 1;
}

void unconcious()
{
	die();
}

void die()
{
        ::die();
}
