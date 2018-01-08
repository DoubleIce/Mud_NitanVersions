// This program is a part of NT mudlib
// boss ģ��

#include <ansi.h>

inherit BOSS;

int big_blowing();

void create()
{
	set_name(HIC "�������" NOR, ({ "jade dragon king", "dragon king", "dragon" }) );
	set("race", "Ұ��");
	set("gender", "����");
	set("age", 200);
	set("long", 
HIC"����һ������֮�������������������ȫ��ɢ��������ɫ�Ĺ�â��\n\n"NOR);

        set("dex",100);
        set("con",100);
        set("int",100);
        set("str",100);

        set("combat_exp", 30000000);
        set("level", 30);
        set("qi", 6000000);
        set("max_qi", 6000000);
        set("jing", 3000000);
        set("max_jing", 3000000);
        set("neili", 12000000);
        set("max_neili", 12000000);
        set("jiali", 60000);

        set("chat_chance", 5);
        set("chat_msg", ({
                HIB "���һ���紵������������ߣ�\n" NOR,
                HIB "�������ͻȻ�³�һ����������ӣ��־��˻�ȥ��\n" NOR,
        }));

        set("chat_chance_combat", 100);
        set("chat_msg_combat", ({
                (: big_blowing :),
        }));

        set_temp("apply/attack", 3000+random(3000));
        set_temp("apply/unarmed_damage",3000+random(3000));
        set_temp("apply/armor", 3000+random(3000));
        set_temp("apply/add_xuruo", 70);
        set_temp("apply/reduce_damage", 80);
        set_temp("apply/reduce_busy", 20);
        set_temp("apply/add_busy", 5);
        
        set("bonus", 80000);
        
        // ��Ʒ����
        set("killer_reward", ([
                "RA&RANDOM90"                                    :       10000,  // �ͼ���ͨװ��
                "RA&RANDOM100"                                    :       300,    // �м���ͨװ��
                "FI&/clone/fam/skpaper/unarmed1"   :   5000,
                "FI&/clone/fam/skpaper/parry1"   :   5000,
                "FI&/clone/enchase/rune13"   :   5000,
                "FI&/clone/enchase/rune14"   :   5000,
                "FI&/clone/enchase/rune15"   :   5000,
                "MO&A1000"       :       300,
                "MO&A1001"       :       300,
                "MO&A1002"       :       300,
                "MO&A1003"       :       300,
                "MO&A1004"       :       300,
                "MO&A1005"       :       300,
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
        message_vision(HIB "$N" HIB "���������һ������ȫ����ҫ�۵���ɫ��"
                       "���������ʹ��˼�������\n" NOR, this_object());

        remove_call_out("hurting");
        call_out("hurting", random(2) + 1);
        return 1;
}

int hurting()
{
        int dam, i , num;
        object *inv;
        
        message_vision(HIB "$N" HIB "�³�һ�ɾ޴����쫷磮������������������ƺ�������û������\n" NOR,
                       this_object());
                       
        inv = all_inventory(environment(this_object()));        

        num = sizeof(inv);       
        if (num < 1) num = 1;
        if (num > 5) num = 5;
        
        dam = 30000 / num;
        
        for (i=sizeof(inv)-1; i>=0; i--)
        {
                if (living(inv[i]) && inv[i] != this_object())
                {
                        dam -= inv[i]->query_temp("apply/reduce_wind");
                        if (dam <0) dam = 0;
                        
                        inv[i]->receive_damage("qi", dam, this_object());
                        inv[i]->receive_damage("jing", dam/2, this_object());
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
        
        damage = 8000 + random(8000);
        damage -= ob->query_temp("apply/reduce_cold");
        if (damage < 0) damage = 0;
        ob->receive_damage("qi", damage, me);
        ob->receive_wound("qi", damage, me);
        me->set("neili", me->query("max_neili"));
        return HIB "$N" HIB "���𡱵�һ���³�һ��쫷磬��ʱ��$n"
               HIB "�о������������ء�\n" NOR;
}

