// This program is a part of NT mudlib
// boss 模板

#include <ansi.h>

inherit NPC;
inherit BOSS;

int big_blowing();

void create()
{
	set_name(HIY "黄金巨龙" NOR, ({ "yellow dragon king", "dragon king", "dragon" }) );
	set("race", "野兽");
	set("gender", "雄性");
	set("age", 200);
	set("long", 
HIY"这是一条全身金黄，在黄沙中长大的神龙！它全身散发着金黄色的光芒！\n\n"NOR);

        set("dex",100);
        set("con",100);
        set("int",100);
        set("str",100);

        set("combat_exp", 50000000);
        set("level", 50);
        set("qi", 10000000);
        set("max_qi", 10000000);
        set("jing", 5000000);
        set("max_jing", 5000000);
        set("neili", 20000000);
        set("max_neili", 20000000);
        set("jiali", 50000);

        set("chat_chance", 5);
        set("chat_msg", ({
                HIB "突然一阵黄沙卷来！差点把你卷走！\n" NOR,
                HIB "黄金巨龙突然吐出一颗金黄的珠子，又卷了回去！\n" NOR,
        }));

        set("chat_chance_combat", 50 + random(10));
        set("chat_msg_combat", ({
                (: big_blowing :),
        }));

        set_temp("apply/attack", 5000+random(5000));
        set_temp("apply/unarmed_damage",5000+random(5000));
        set_temp("apply/armor", 5000+random(5000));
        
        // 物品奖励
	set("killer_reward", killer_reward("yellow_dragon"));

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
        message_vision(HIB "$N" HIB "从黄沙里深深地吸入一口气，全身发出耀眼的金色，"
                       "整个龙腹胀大了几倍！！\n" NOR, this_object());

        remove_call_out("hurting");
        call_out("hurting", random(2) + 1);
        return 1;
}

int hurting()
{
        int dam, i , num;
        object *inv;
        
        message_vision(HIB "$N" HIB "喷出一团巨大的黄沙．．．．．．整个天地都被黄沙吞没！！！\n" NOR,
                       this_object());
                       
        inv = all_inventory(environment(this_object()));        

        num = sizeof(inv);       
        if (num < 1) num = 1;
        if (num > 5) num = 5;
        
        dam = 5000 / num;
        
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
        
        damage = 3000 + random(3000);
        damage -= ob->query_temp("apply/reduce_cold");
        if (damage < 0) damage = 0;
        ob->receive_wound("qi", damage, me);
        me->set("neili", me->query("max_neili"));
        return HIB "$N" HIB "“吼”的一声吐出一片黄沙，登时令$n"
               HIB "犹如千针加身。\n" NOR;
}

void unconcious()
{
        die();
}

void die()
{
        ::die();
}

