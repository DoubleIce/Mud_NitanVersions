// This program is a part of NT mudlib
// boss ģ��

#include <ansi.h>

inherit NPC;
inherit BOSS;

int big_blowing();

void create()
{
	set_name(HIR "��צ����" NOR, ({ "jiuzhao nielong", "nielong", "nie long" }) );
	set("race", "Ұ��");
	set("gender", "����");
	set("age", 200);
	set("long", 
HIR"����һ��ȫ���죬�����֮��Ļ������������������ȫ��ɢ���ų��ɫ�Ļ��棡\n\n"NOR);

        set("dex",100);
        set("con",100);
        set("int",100);
        set("str",100);

        set("combat_exp", 10000000);
        set("level", 10);
        set("qi", 2000000);
        set("max_qi", 2000000);
        set("jing", 1000000);
        set("max_jing", 1000000);
        set("neili", 4000000);
        set("max_neili", 4000000);
        set("neili", 4000000);
        set("jiali", 10000);

        set("chat_chance", 5);
        set("chat_msg", ({
                HIB "һ�Ż�����˹������������ճɻң�\n" NOR,
                HIB "��צ����ͻȻ�³�һ�ų��Ļ��棡\n" NOR,
        }));

        set("chat_chance_combat", 50 + random(10));
        set("chat_msg_combat", ({
                (: big_blowing :),
        }));

        set_temp("apply/attack", 1000+random(1000));
        set_temp("apply/unarmed_damage",1000+random(1000));
        set_temp("apply/armor", 1000+random(1000));
        
        // ��Ʒ����
	set("killer_reward", killer_reward("nielong"));

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
        message_vision(HIB "$N" HIB "�ӻ��������������һ�ڻ�����ȫ��תΪ�ʺ�Ļ�ɫ��"
                       "���������ʹ��˼�������\n" NOR, this_object());

        remove_call_out("hurting");
        call_out("hurting", random(2) + 1);
        return 1;
}

int hurting()
{
        int dam, i , num;
        object *inv;
        
        message_vision(HIB "$N" HIB "�³�һ�ɳ�ɷٽ�Ļ��森������������������ƺ�����ȼ���ţ�����\n" NOR,
                       this_object());
                       
        inv = all_inventory(environment(this_object()));        

        num = sizeof(inv);       
        if (num < 1) num = 1;
        if (num > 5) num = 5;
        
        dam = 2500 / num;
        
        for (i=sizeof(inv)-1; i>=0; i--)
        {
                if (living(inv[i]) && inv[i] != this_object())
                {
                        dam -= inv[i]->query_temp("apply/reduce_fire");
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
        
        damage = 500 + random(500);
        damage -= ob->query_temp("apply/reduce_cold");
        if (damage < 0) damage = 0;
        ob->receive_wound("qi", damage, me);
        me->set("neili", me->query("max_neili"));
        return HIB "$N" HIB "��������һ���³�һ�Ż��򣬵�ʱ��$n"
               HIB "���������ˡ�\n" NOR;
}

void unconcious()
{
        die();
}

void die()
{
        ::die();
}

