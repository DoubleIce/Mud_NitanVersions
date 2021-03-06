#include <ansi.h>
inherit NPC;
inherit BOSS;

int showpower1();
int showpower2();
int combatpower();
int powerup();

void create()
{
	set_name("雷神", ({ "lei shen", "leishen", "lei" }) );
	set("title", HIY"雷王 "HIG"五方雷霆大帝"NOR );
	set("long", "五方雷王，看上去耳朵很长，手中持一对铁罄。\n");
	set("nickname",HIR"太阳轰"NOR);
	set("name_color", "HIC");
	set("gender", "男性");
	set("age", 220);
        
	set("str", 48);
	set("con", 52);
	set("dex", 22);

	set("max_qi", 45000);
	set("max_jing", 45000);
	set("max_gin", 40000);
	set("max_mana",40000);
	set("mana",40000);
	set("max_neili",40000);
	set("neili",40000);
	set("attitude", "aggressive");

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
	
	set("bonus", 4000);
	set("killer_reward", killer_reward("leishen"));

	setup();
	carry_object("/clone/money/gold")->set_amount(1);
  	carry_object(WEAPON_DIR"hammer/leigonghong");

	// init_npc(this_object(), 3, 13, 0, 100);
// 自动配置NPC属性和技能，第一个参数必须。
// 第一个参数为NPC的OB
// 第二个参数为NPC的门派，1普陀2地府3方寸4月宫5雪山6五庄7龙宫8无底洞其他为基本，不设置为随机门派
// 第三个参数为NPC的技能，按NPC的等级设置(1:50)，缺省或0为不设置
// 第四个参数为NPC的属性和状态等级，按NPC的等级设置，缺省或0为不设置
// 第五个参数为NPC的强度，缺省为100
}

int showpower1()
{
	tell_object(environment(this_object()),HIY"\n\n\t天上闪过一个霹雳！\n\n\n"NOR);
	return 1;
}
int showpower2()
{
	tell_object(environment(this_object()),HIY"\n\n\t天上闪过一个霹雳！\n\n\n"NOR);
	return 1;
}

int combatpower()
{
	command("unwield bintiegun");
	command("wield hammer");
	tell_object(environment(this_object()),HIY"\n\t天上闪过一个霹雳！\n\n"NOR);
	command("unwield hammer");
	remove_call_out("powerup");
	call_out("powerup",random(10)+2);
	return 1;
}

int powerup()
{
	int dam, i , num;
	object *inv;
	message_vision( HIY"\n一道电光击中了你！！！\n",this_object());
        inv = all_inventory(environment(this_object()));
        num = sizeof(inv);
        if (num < 1) num = 1;
        if (num > 5) num = 5;
        dam = 3000 / num;
        for(i=sizeof(inv)-1; i>=0; i--)
        {
        	if( living(inv[i]) && inv[i] != this_object() )
        	{
        		dam = dam - inv[i]->query_combat_level("DF_spells");
        		if(dam <0) dam = 0;
        		inv[i]->receive_wound("qi", dam, this_object());
        		inv[i]->receive_wound("jing", dam, this_object());
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
