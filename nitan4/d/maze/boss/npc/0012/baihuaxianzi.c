// This program is a part of NT mudlib
// boss ģ��

#include <ansi.h>

inherit NPC;
inherit BOSS;

int big_blowing();

void create()
{
	set_name(HIM "�ٻ�����" NOR, ({ "baihua xianzi", "baihua", "xianzi" }) );
	set("gender", "Ů��");
	set("age", 220);
	set("long", 
HIM"����ĸ�ĵ��ӡ�����ĸ֮������˾������������Ⱥ��֮����
�����϶����������ݺ������ط����������������������
��㺮�����������ơ��ٻ���Ϊ�����˼䣬��һ��Һ��\n\n"NOR);

        set("dex",100);
        set("con",100);
        set("int",100);
        set("str",100);

        set("combat_exp", 70000000);
        set("level", 70);
        set("qi", 14000000);
        set("max_qi", 14000000);
        set("jing", 7000000);
        set("max_jing", 7000000);
        set("neili", 28000000);
        set("max_neili", 28000000);
        set("jiali", 70000);

        set("chat_chance", 5);
        set("chat_msg", ({
                HIM "�����д���һ����磡��������ߣ�\n" NOR,
                HIM "�����д���һ����磡�������˹�ȥ��\n" NOR,
        }));

        set("chat_chance_combat", 50 + random(10));
        set("chat_msg_combat", ({
                (: big_blowing :),
        }));

        set_temp("apply/attack", 7000+random(7000));
        set_temp("apply/unarmed_damage",7000+random(7000));
        set_temp("apply/armor", 7000+random(7000));
        
        // ��Ʒ����
	set("killer_reward", killer_reward("baihuaxianzi"));

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
        message_vision(HIB "$N" HIM "ͻȻ�������ĵ�һЦ����\n" NOR, this_object());

        remove_call_out("hurting");
        call_out("hurting", random(2) + 1);
        return 1;
}

int hurting()
{
        int dam, i , num;
        object *inv;
        
        message_vision(HIB "$N" HIM "�����д���һ����磡�������˹�ȥ������\n" NOR,
                       this_object());
                       
        inv = all_inventory(environment(this_object()));        

        num = sizeof(inv);       
        if (num < 1) num = 1;
        if (num > 5) num = 5;
        
        dam = 7000 / num;
        
        for (i=sizeof(inv)-1; i>=0; i--)
        {
                if (living(inv[i]) && inv[i] != this_object())
                {
                        dam -= inv[i]->query_temp("apply/reduce_wind");
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
        
        damage = 7000 + random(7000);
        damage -= ob->query_temp("apply/reduce_fire");
        if (damage < 0) damage = 0;
        ob->receive_wound("qi", damage, me);
        me->set("neili", me->query("max_neili"));
        return HIB "$N" HIB "���١���һ���ų�һ���꣬��ʱ��$n"
               HIB "ʧȥ���ң����������Ż��С�\n" NOR;
}

void unconcious()
{
        die();
}

void die()
{
        ::die();
}

