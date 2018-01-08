// Code of ShenZhou
// Ryu, 11/20/96.

#include <ansi.h>
inherit NPC;

void create()
{
        set_name(YEL"蝎子"NOR, ({ "scorpion", "xiezi" }) );
        set("race", "昆虫");
        set("subrace", "爬虫");
        set("age", 3);
        set("long", "一只褐色的蝎子，尾巴上有黄蓝相间的环纹。\n");
        set("attitude", "peaceful");

//        set("limbs", ({ "头部", "身体", "触角", "前螯", "尾巴" }) );
//        set("verbs", ({ "bite", "claw" }) );

        set("combat_exp", 900);
        set_temp("apply/attack", 10);
        set_temp("apply/defense", 6);
        set_temp("apply/armor", 1);

        set("insect_poison", ([
                "level"  : 80,
                "maximum": 50,
        ]));

        setup();
}
void init()
{
        object ob;
        ::init();
        if (interactive(ob = this_player()) &&
                random(ob->query_kar() + ob->query_per()) < 30) {
                        remove_call_out("kill_ob");
                        call_out("kill_ob", 1, ob);
        }
}
void die()
{
        object ob;
        message_vision("\n$N尾巴一翘，死了。\n", this_object());
        ob = new("/d/xingxiu/npc/scorp_shell");
        ob->move(environment(this_object()));
        destruct(this_object());
}
