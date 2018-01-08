#include <ansi.h>
inherit NPC;
string *first_name = ({ "ɳ", "��"});
string *first_id = ({ "sha", "ash"});
string *name_words = ({ "Ы", "ħ"});
string *id_words = ({ "xie", "mo"});
int combatpower();

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
        
        set("combat_exp", 25000000);
        set("level", 25);
        set("qi", 500000);
        set("max_qi", 500000);
        set("jing", 250000);
        set("max_jing", 250000);
        set("neili", 1000000);
        set("max_neili", 1000000);
        set("jiali", 5000);

        set_skill("unarmed", 2500); 
        set_skill("dodge", 2500); 
        set_skill("parry", 2500); 
        set_skill("force", 2500); 
	

	set_temp("apply/attack", 2500+random(2500));
	set_temp("apply/unarmed_damage",2500+random(2500));
	set_temp("apply/armor", 2500+random(2500));        

	set("killer_reward", 
		([
		"QU&MODMP1"					:	1000,	// һ��������װ
		"QU&MODMP2"					:	200,	// ����������װ
		"QU&MODMP3"					:	10,	// ����������װ
		"QU&GENER1"					:	2000,	// �ͼ���ͨװ��
		"QU&GENER2"					:	300,	// �м���ͨװ��
		"QU&GENER3"					:	20,	// �߼���ͨװ��
	])
	);

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
        
        damage = 400 + random(400);
        damage -= ob->query_temp("apply/reduce_cold");
        if (damage < 0) damage = 0;
        ob->receive_wound("qi", damage, me);
        me->set("neili", me->query("max_neili"));
        return HIC "$N" HIC "��������һ������һ���ɳ����ʱ��$n"
               HIC "����ǧ�����\n" NOR;
}

void unconcious()
{
	die();
}

void die()
{
        ::die();
}


