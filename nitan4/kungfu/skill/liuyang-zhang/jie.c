// This program is a part of NITAN MudLIB
// jie.c 解生死符 

#include <ansi.h>
inherit F_SSERVER;
int perform(object me, object target)
{
        object obj;
        string msg;

        if (! target) target = offensive_target(me);

        if (userp(me) && ! me->query("can_perform/liuyang-zhang/zhong"))
                return notify_fail("你虽听过生死符的名字，但是不懂得如何催动内力解符。\n");

        if (! target || ! target->is_character())
                return notify_fail("你要解谁的生死符？\n");

        if (((int)me->query_skill("bahuang-gong", 1) < 40 ) &&
            ((int)me->query_skill("beiming-shengong", 1) < 40 ))
                return notify_fail("你的本门内功不够娴熟，不能解生死符。\n");

        if ((int)me->query_skill("liuyang-zhang", 1) < 150)
                return notify_fail("你的天山六阳掌不够娴熟，不能解生死符。\n");

        if (! objectp(obj = present("jiudai", me)))
                return notify_fail("你身上没有酒袋，无法化冰解毒。\n");

        if (me->query("neili") < 200)
                return notify_fail("你真气不足。\n");

        if (! target->query_condition("ss_poison"))
                return notify_fail("目标没有中生死符。\n");

        message_combatd(HIY CYN "\n$N面色突冷，身行疾转连续拍向$n八八六十四掌，解开了$n的生死符毒。\n" NOR, me, target);
        me->add("neili", -200);
        me->start_busy(2);
        target->apply_condition("ss_poison", 0);
        return 1;
}

