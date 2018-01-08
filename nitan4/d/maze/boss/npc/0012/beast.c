#include <ansi.h>
inherit NPC;
string *first_name = ({ "��", "�ٻ�"});
string *first_id = ({ "hua", "baihua"});
string *name_words = ({ "��", "����"});
string *id_words = ({ "xian", "xianzi"});
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
        
        set("combat_exp", 35000000);
        set("level", 35);
        set("qi", 700000);
        set("max_qi", 700000);
        set("jing", 350000);
        set("max_jing", 350000);
        set("neili", 1400000);
        set("max_neili", 1400000);
        set("jiali", 7000);

        set_skill("unarmed", 3500); 
        set_skill("dodge", 3500); 
        set_skill("parry", 3500); 
        set_skill("force", 3500); 
	

	set_temp("apply/attack", 3500+random(3500));
	set_temp("apply/unarmed_damage",3500+random(3500));
	set_temp("apply/armor", 3500+random(3500));        

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
        
        damage = 700 + random(700);
        damage -= ob->query_temp("apply/reduce_cold");
        if (damage < 0) damage = 0;
        ob->receive_wound("qi", damage, me);
        me->set("neili", me->query("max_neili"));
        return HIC "$N" HIC "��������һ������ð�����ľ�̣���ʱ��$n"
               HIC "������Ѫ������\n" NOR;
}

void unconcious()
{
	die();
}

void die()
{
        ::die();
}


