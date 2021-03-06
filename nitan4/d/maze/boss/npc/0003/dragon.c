// This program is a part of NT mudlib
// boss 模板

#include <ansi.h>

inherit BOSS;

int big_blowing();

void create()
{
	set_name(HIW "苍云巨龙" NOR, ({ "cloud dragon king", "dragon king", "dragon" }) );
	set("race", "野兽");
	set("gender", "雄性");
	set("age", 200);
	set("long", 
HIC"这是一条全身晶莹雪白，吸风云之精华而长大的神龙！它全身散发着白玉的光芒！\n\n"NOR);

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
                HIB "一团白云飘来！差点把你卷走！\n" NOR,
                HIB "苍云巨龙突然吐出一颗晶莹的珠子，又卷了回去！\n" NOR,
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
        // 物品奖励
        set("killer_reward", ([
                "FI&/clone/fam/skpaper/whip1"   :   5000,
                "FI&/clone/fam/skpaper/club1"   :   5000,
                "FI&/clone/fam/skpaper/hammer1"   :   5000,
                "FI&/clone/enchase/rune16"   :   5000,
                "FI&/clone/enchase/rune17"   :   5000,
                "FI&/clone/enchase/rune18"   :   5000,
                "FI&/clone/enchase/rune19"   :   5000,
                "RA&RANDOM100"                         :       10000,    // 中级普通装备
                "RA&RANDOM110"                         :       1000,    // 中级普通装备
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
        message_vision(HIB "$N" HIB "从白云里深深地吸入一口气，全身发出耀眼的白色，"
                       "整个龙腹胀大了几倍！！\n" NOR, this_object());

        remove_call_out("hurting");
        call_out("hurting", random(2) + 1);
        return 1;
}

int hurting()
{
        int dam, i , num;
        object *inv;
        
        message_vision(HIB "$N" HIB "吐出一股巨大的雷云．．．．．．整个天地似乎都被吞没！！！\n" NOR,
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
        return HIB "$N" HIB "“吼”的一声吐出一片雷云，登时令$n"
               HIB "五雷轰顶。\n" NOR;
}

