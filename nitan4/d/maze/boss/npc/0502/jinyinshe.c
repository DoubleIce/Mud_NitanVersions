// This program is a part of NT mudlib
// boss ģ��

#include <ansi.h>

inherit NPC;
inherit BOSS;

int big_blowing();

void create()
{
	set_name(HIG "������" NOR, ({ "jinyin she", "yinhui", "yin she", "she" }) );
	set("race", "Ұ��");
	set("gender", "����");
	set("age", 200);
	set("long", 
HIG"����һ��ȫ����̣������֮�����������ľ�������ȫ��ɢ���ű���ɫ�Ĺ�â��\n\n"NOR);

        set("dex",100);
        set("con",100);
        set("int",100);
        set("str",100);

        set("combat_exp", 15000000);
        set("level", 15);
        set("qi", 3000000);
        set("max_qi", 3000000);
        set("jing", 1500000);
        set("max_jing", 1500000);
        set("neili", 6000000);
        set("max_neili", 6000000);
        set("jiali", 15000);

        set("chat_chance", 5);
        set("chat_msg", ({
                HIB "һ�Ŷ��̾��˹������������ճɻң�\n" NOR,
                HIB "������ͻȻ�³�һ�ű��̵Ķ��̣�\n" NOR,
        }));

        set("chat_chance_combat", 50 + random(10));
        set("chat_msg_combat", ({
                (: big_blowing :),
        }));

        set_temp("apply/attack", 1500+random(1500));
        set_temp("apply/unarmed_damage",1500+random(1500));
        set_temp("apply/armor", 1500+random(1500));
        
        // ��Ʒ����
	set("killer_reward", killer_reward("jinyinshe"));

        setup();
        carry_object("/clone/money/gold")->set_amount(200);
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

int big_blowing()
{
        message_vision(HIB "$N" HIB "���������һ������ȫ���������Ĺ�â��"
                       "�����߸��ʹ��˼�������\n" NOR, this_object());

        remove_call_out("hurting");
        call_out("hurting", random(2) + 1);
        return 1;
}

int hurting()
{
        int dam, i , num;
        object *inv;
        
        message_vision(HIB "$N" HIB "�³�һ�ɱ��̵Ķ��̣������������������˹�ȥ������\n" NOR,
                       this_object());
                       
        inv = all_inventory(environment(this_object()));        

        num = sizeof(inv);       
        if (num < 1) num = 1;
        if (num > 5) num = 5;
        
        dam = 3500 / num;
        
        for (i=sizeof(inv)-1; i>=0; i--)
        {
                if (living(inv[i]) && inv[i] != this_object())
                {
                        dam -= inv[i]->query_temp("apply/reduce_poison");
                        if (dam <0) dam = 0;
                        
                        inv[i]->receive_wound("qi", dam, this_object());
                        inv[i]->receive_wound("jing", dam/2, this_object());
                        COMBAT_D->report_status(inv[i], 1);
                }
        }
        return 1;
}

mixed hit_ob(object me, object ob, int damage_bouns)
{
        int damage;
        
        damage = 1000 + random(1000);
        damage -= ob->query_temp("apply/reduce_cold");
        if (damage < 0) damage = 0;
        ob->receive_wound("qi", damage, me);
        me->set("neili", me->query("max_neili"));
        return HIB "$N" HIB "��������һ���³�һ�Ŷ�����ʱ��$n"
               HIB "��֫�ܵ�������ʴ��\n" NOR;
}

void unconcious()
{
        die();
}

void die()
{
        ::die();
}

