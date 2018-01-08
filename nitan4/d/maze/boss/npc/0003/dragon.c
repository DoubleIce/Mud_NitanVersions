// This program is a part of NT mudlib
// boss ģ��

#include <ansi.h>

inherit BOSS;

int big_blowing();

void create()
{
	set_name(HIW "���ƾ���" NOR, ({ "cloud dragon king", "dragon king", "dragon" }) );
	set("race", "Ұ��");
	set("gender", "����");
	set("age", 200);
	set("long", 
HIC"����һ��ȫ��Өѩ�ף�������֮�������������������ȫ��ɢ���Ű���Ĺ�â��\n\n"NOR);

        set("dex",100);
        set("con",100);
        set("int",100);
        set("str",100);

        set("combat_exp", 40000000);
        set("level", 40);
        set("qi", 8000000);
        set("max_qi", 8000000);
        set("jing", 4000000);
        set("max_jing", 4000000);
        set("neili", 16000000);
        set("max_neili", 16000000);
        set("jiali", 40000);

        set("chat_chance", 5);
        set("chat_msg", ({
                HIB "һ�Ű���Ʈ������������ߣ�\n" NOR,
                HIB "���ƾ���ͻȻ�³�һ�ž�Ө�����ӣ��־��˻�ȥ��\n" NOR,
        }));

        set("chat_chance_combat", 100);
        set("chat_msg_combat", ({
                (: big_blowing :),
        }));

        set_temp("apply/attack", 4000+random(4000));
        set_temp("apply/unarmed_damage",4000+random(4000));
        set_temp("apply/armor", 8000+random(8000));
        set_temp("apply/add_xuruo", 80);
        set_temp("apply/reduce_damage", 80);
        set_temp("apply/reduce_busy", 20);
        set_temp("apply/add_busy", 5);
        
        set("bonus", 80000);
        // ��Ʒ����
        set("killer_reward", ([
                "FI&/clone/fam/skpaper/whip1"   :   5000,
                "FI&/clone/fam/skpaper/club1"   :   5000,
                "FI&/clone/fam/skpaper/hammer1"   :   5000,
                "FI&/clone/enchase/rune16"   :   5000,
                "FI&/clone/enchase/rune17"   :   5000,
                "FI&/clone/enchase/rune18"   :   5000,
                "FI&/clone/enchase/rune19"   :   5000,
                "RA&RANDOM100"                         :       10000,    // �м���ͨװ��
                "RA&RANDOM110"                         :       1000,    // �м���ͨװ��
        ]));

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

varargs void start_busy(mixed new_busy, mixed new_interrupt)
{
        return;
}

int big_blowing()
{
        message_vision(HIB "$N" HIB "�Ӱ��������������һ������ȫ����ҫ�۵İ�ɫ��"
                       "���������ʹ��˼�������\n" NOR, this_object());

        remove_call_out("hurting");
        call_out("hurting", random(2) + 1);
        return 1;
}

int hurting()
{
        int dam, i , num;
        object *inv;
        
        message_vision(HIB "$N" HIB "�³�һ�ɾ޴�����ƣ�������������������ƺ�������û������\n" NOR,
                       this_object());
                       
        inv = all_inventory(environment(this_object()));        

        num = sizeof(inv);       
        if (num < 1) num = 1;
        if (num > 5) num = 5;
        
        dam = 40000 / num;
        
        for (i=sizeof(inv)-1; i>=0; i--)
        {
                if (living(inv[i]) && inv[i] != this_object())
                {
                        dam -= inv[i]->query_temp("apply/reduce_cloud");
                        if (dam <0) dam = 0;
                        
                        inv[i]->receive_damage("qi", dam, this_object());
                        inv[i]->receive_damage("jing", dam, this_object());
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
        
        damage = 10000 + random(10000);
        damage -= ob->query_temp("apply/reduce_cold");
        if (damage < 0) damage = 0;
        ob->receive_damage("qi", damage, me);
        ob->receive_wound("qi", damage, me);
        me->set("neili", me->query("max_neili"));
        return HIB "$N" HIB "���𡱵�һ���³�һƬ���ƣ���ʱ��$n"
               HIB "���׺䶥��\n" NOR;
}

