// shedu-qiqiao.c

inherit SKILL;

int valid_enable(string usage) { return usage == "poison"; }

int valid_learn(object me)
{
        if ((int)me->query_skill("force") < 80)
                return notify_fail("你的内功火候不够，无法学习妙手驱毒。\n");

        if ((int)me->query("max_neili") < 350)
                return notify_fail("你的内力太弱，无法学习妙手驱毒。\n");

        if ((int)me->query_skill("poison", 1) < 30)
                return notify_fail("你的基本毒技火候不够，无法学妙手驱毒。\n");

        if ((int)me->query_skill("poison", 1) < (int)me->query_skill("dispel-poison", 1))
                return notify_fail("你的基本毒技水平有限，无法领会更高深的妙手驱毒。\n");

        return 1;
}

int practice_skill(object me)
{
        return notify_fail("妙手驱毒只能通过学习获得长进。\n");
}
