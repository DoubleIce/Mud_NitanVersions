// This program is a part of NT mudlib
// boss 模板

#include <ansi.h>

inherit NPC;
inherit BOSS;

int big_blowing();

void create()
{
	set_name(HIM "百花仙子" NOR, ({ "baihua xianzi", "baihua", "xianzi" }) );
	set("gender", "女性");
	set("age", 220);
	set("long", 
HIM"西王母的弟子。奉王母之命，总司天下名花，乃群芳之主。
因与嫦娥不睦，遭其陷害，被谪凡尘。厄满后独居蓬莱，不
与广寒宫来往，所制“百花酿”为天上人间，第一玉液。\n\n"NOR);

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
                HIM "花丛中吹来一阵香风！差点把你卷走！\n" NOR,
                HIM "花丛中吹来一阵香风！你差点晕了过去！\n" NOR,
        }));

        set("chat_chance_combat", 50 + random(10));
        set("chat_msg_combat", ({
                (: big_blowing :),
        }));

        set_temp("apply/attack", 7000+random(7000));
        set_temp("apply/unarmed_damage",7000+random(7000));
        set_temp("apply/armor", 7000+random(7000));
        
        // 物品奖励
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
        message_vision(HIB "$N" HIM "突然朝你妩媚的一笑！！\n" NOR, this_object());

        remove_call_out("hurting");
        call_out("hurting", random(2) + 1);
        return 1;
}

int hurting()
{
        int dam, i , num;
        object *inv;
        
        message_vision(HIB "$N" HIM "花丛中吹来一阵香风！你差点晕了过去！！！\n" NOR,
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
        return HIB "$N" HIB "“嘿”的一声放出一阵花雨，登时令$n"
               HIB "失去自我，被花雨屡屡击中。\n" NOR;
}

void unconcious()
{
        die();
}

void die()
{
        ::die();
}

