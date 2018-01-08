#include <ansi.h>
inherit NPC;
string *first_name = ({ "��", "���"});
string *first_id = ({ "tian", "sky"});
string *name_words = ({ "����", "��"});
string *id_words = ({ "juling", "yao"});

void create()
{
        string name;
        int i, j;
        
        i = random(sizeof(first_name));
        name = first_name[i];
        j = random(sizeof(name_words));
        name += name_words[j];

        set_name(name, ({ first_id[i]+" "+id_words[j] }) );
        // random_name_color(this_object());
        
        set("age", 20);
        set("vrm_guard", 1);
        set("attitude", "aggressive");

        set("dex",100);
        set("con",100);
        set("int",100);
        set("str",100);
        
        set("combat_exp", 15000000);
        set("level", 15);
        set("qi", 300000);
        set("max_qi", 300000);
        set("jing", 150000);
        set("max_jing", 150000);
        set("neili", 600000);
        set("max_neili", 600000);
        set("jiali", 6000);

        set_skill("unarmed", 1500); 
        set_skill("dodge", 1500); 
        set_skill("parry", 1500); 
        set_skill("force", 1500); 
	

	set_temp("apply/attack", 1500+random(1500));
	set_temp("apply/unarmed_damage",1500+random(1500));
	set_temp("apply/armor", 1500+random(1500));        

        set("killer_reward", ([
                "RA&RANDOM50"                                    :       10000,  // �ͼ���ͨװ��
                "RA&RANDOM60"                                    :       300,    // �м���ͨװ��
                "MO&A1000"       :       300,
                "MO&A1001"       :       300,
                "MO&A1002"       :       300,
                "MO&A1003"       :       300,
                "MO&A1004"       :       300,
                "MO&A1005"       :       300,
        ]));


	set_weight(500000);
        setup();
}
       
void init()
{
        object me, ob;

        ::init();
        if (! interactive(me = this_player()))
                return;

        remove_call_out("kill_ob");
        call_out("kill_ob", 0, me);
}
        
mixed hit_ob(object me, object ob, int damage_bouns)
{
        int damage;
        
        damage = 300 + random(300);
        damage -= ob->query_temp("apply/reduce_cold");
        if (damage < 0) damage = 0;
        ob->receive_wound("qi", damage, me);
        me->set("neili", me->query("max_neili"));
        return HIC "$N" HIC "��������һ������һ���磬��ʱ��$n"
               HIC "�������絶��һ�㡣\n" NOR;
}

void unconcious()
{
	die();
}

void die()
{
        ::die();
}


