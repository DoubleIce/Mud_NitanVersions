// This program is a part of NITAN MudLIB
// powerup.c

#include <ansi.h>
inherit F_CLEAN_UP;
void remove_effect(object me, int amount);

int exert(object me, object target)
{
        int skill;
        if (target != me) 
                return notify_fail("你只能用北冥神功提升自己的战斗力。\n");
                
        if ((int)me->query("neili") < 100) 
                return notify_fail("你的内力不够。\n");
                
        if ((int)me->query_temp("powerup")) 
                return notify_fail("你已经在运功中了。\n");

        skill = me->query_skill("force");

        me->add("neili", -100);
        me->receive_damage("qi", 0);

        message_combatd(MAG "$N" MAG "长长吸了口气，神凝丹田，息游紫府，身若"
                        "凌虚而超华岳，气如冲霄而撼北辰。\n" NOR, me);

        me->add_temp("apply/attack", skill / 5);
        me->add_temp("apply/defense", skill / 5);
        me->set_temp("powerup", 1);
        
        me->start_call_out((: call_other, __FILE__, "remove_effect",
                           me, skill / 5 :), skill);
        
        if (me->is_fighting()) me->start_busy(3);
        return 1;
}

void remove_effect(object me, int amount)
{
        if ((int)me->query_temp("powerup"))
        {
                me->add_temp("apply/attack", -amount);
                me->add_temp("apply/defense", -amount);
                me->delete_temp("powerup");
                tell_object(me, "你的北冥神功运行完毕，将内力收回丹田。\n");
        }
}


