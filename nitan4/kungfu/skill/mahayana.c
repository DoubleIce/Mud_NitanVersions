//mahayana.c  大乘涅磐功
#include <ansi.h>
inherit SKILL;

string type() { return "knowledge"; }

int valid_learn(object me)
{
    if ((int)me->query("shen") < 0 )
       return notify_fail("你的邪气太重，无法修炼大乘涅磐功。\n");

    return 1;
}

void skill_improved(object me)
{
        if ((int)me->query_skill("mahayana", 1) == 120 && ! me->query("em/dex") && me->query("gender") != "男性")
        {
                me->add("dex", 1);
                me->set("em/dex", 1);
                tell_object(me, HIM "\n你的大乘涅磐功学有所成，提高了你的身法。\n" NOR);
        }
}
