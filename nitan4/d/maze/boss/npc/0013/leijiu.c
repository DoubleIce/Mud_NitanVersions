#include <ansi.h>
inherit NPC;
inherit BOSS;

int showpower1();
int showpower2();
int combatpower();
int powerup();

void create()
{
	set_name("��������", ({ "jinpeng leijiu", "jinpeng", "leijiu" }) );
	set("name_color","HIY");
	set("gender", "Ů��");
	set("age", 220);
	set("long", 
HIY"�����Ľ�����ȫ���ƣ���ʮ�ɣ��ƺ��õ����ꡣ\n\n"NOR);
        
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
	
	set("bonus", 2000);
	set("killer_reward", killer_reward("leijiu"));

	setup();
	carry_object("/clone/money/gold")->set_amount(1);

	// init_npc(this_object(), 3, 8, 0, 100);
// �Զ�����NPC���Ժͼ��ܣ���һ���������롣
// ��һ������ΪNPC��OB
// �ڶ�������ΪNPC�����ɣ�1����2�ظ�3����4�¹�5ѩɽ6��ׯ7����8�޵׶�����Ϊ������������Ϊ�������
// ����������ΪNPC�ļ��ܣ���NPC�ĵȼ�����(1:50)��ȱʡ��0Ϊ������
// ���ĸ�����ΪNPC�����Ժ�״̬�ȼ�����NPC�ĵȼ����ã�ȱʡ��0Ϊ������
// ���������ΪNPC��ǿ�ȣ�ȱʡΪ100
}

int showpower1()
{
	tell_object(environment(this_object()),HIY"\tһ����ɫ�Ļ���ȼ�������������Ϣһ�ϣ�\n"NOR);
	return 1;
}
int showpower2()
{
	tell_object(environment(this_object()),HIY"\tһ������ը�����������Ϣһ�ϣ�\n"NOR);
	return 1;
}

int combatpower()
{
	message_vision( HIY"\nһ����ɫ�Ļ���ȼ��������$N˫��һչ������������������\n" NOR,this_object());
	remove_call_out("powerup");
	call_out("powerup",random(10)+2);
	return 1;
}

int powerup()
{
	int dam, i , num;
	object *inv;
	message_vision( HIY"\n��ƵĻ�������������������˹�ȥ������\n",this_object());
        inv = all_inventory(environment(this_object()));
        num = sizeof(inv);
        if (num < 1) num = 1;
        if (num > 5) num = 5;
        dam = 2000 / num;
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
