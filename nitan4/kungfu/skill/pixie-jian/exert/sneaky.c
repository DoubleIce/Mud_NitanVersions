// This program is a part of NITAN MudLIB
// sneaky.c

#include <ansi.h>

inherit F_CLEAN_UP;

void remove_effect(object me, int amount);

int exert(object me, object target)
{
        int skill;
        
        if (userp(me) && ! me->query("reborn/times"))
                return notify_fail("你所使用的内功中没有这种功能。\n");
                
        if (target != me)
                return notify_fail("辟邪剑法只能对自己使用。\n");

        if ((int)me->query("neili") < 100)
                return notify_fail("你的真气不够！\n");

        if (me->query_skill("pixie-jian", 1) < 120)
                return notify_fail("你的辟邪剑法修行不够，难以运功。\n");

        if ((int)me->query_temp("apply/shade_vision"))
                return notify_fail("你已经在运功中了。\n");

        skill = me->query_skill("force");

        me->add("neili", -100);
        me->receive_damage("qi", 0);
        
        message_combatd( HIW "$N" HIW "微一凝神，运起功力，整个人如同被烟雾笼罩一般，漂忽不定，鬼魅至极。\n" NOR, me);

        me->set_temp("apply/shade_vision",1);
        me->start_call_out((: call_other, __FILE__, "remove_effect",
                           me, skill :), skill);

        if (me->is_fighting()) me->start_busy(3);

        return 1;
}

void remove_effect(object me, int level)
{
        if (me->query_temp("apply/shade_vision"))
        {
                me->delete_temp("apply/shade_vision");
                message_vision(HIW "$N" HIW "运功完毕，全身忽的一顿，现出整个身形。\n" NOR, me);
        }
}

