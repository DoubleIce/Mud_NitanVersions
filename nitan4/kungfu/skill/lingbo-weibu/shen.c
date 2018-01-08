// This program is a part of NITAN MudLIB

#include <ansi.h>

#define LING "「" MAG "神光离合" NOR "」"

void remove_effect(object me);

int perform(object me, object target)
{
        string msg;
        
        if( me->query("family/family_name") != "逍遥派" )
                return notify_fail("你不是逍遥派弟子，无法施展" LING "。\n" NOR);

        if( !me->query("reborn/times") )        
                return notify_fail("你尚未转世重生，无法施展" LING "。\n" NOR);

        if( me->query_skill("lingbo-weibu", 1) < 1000 )
                return notify_fail("你的凌波微步还不够熟练，难以施展" LING "。\n" NOR);

        if( (int)me->query("jingli") < 2000 )
                return notify_fail("你现在真气不足，难以施展" LING "。\n" NOR);

        if( (int)me->query("neili") < 5000 )
                return notify_fail("你现在内力不够，难以施展" LING "。\n" NOR);
                
        if (me->query_temp("immortal"))
                return notify_fail("你已经运起" LING "。\n" NOR);

        me->add("neili", -1000);
        me->receive_damage("qi", 0);
        me->set_temp("immortal", 1);

        msg = MAG "\n$N" MAG "提起真气，施展" LING + "，身形虚晃，神光交错，离合难分，让人难以看清所在。\n" NOR;

        message_combatd(msg, me);
        
        me->start_call_out((: call_other, __FILE__, "remove_effect", me :), 15);
        
        if( me->is_fighting() ) me->start_busy(2);
        return 1;

}

void remove_effect(object me)
{
        if ((int)me->query_temp("immortal"))
        {
                me->delete_temp("immortal");
                tell_object(me, "你的「神光离合」运功完毕，将内力收回丹田。\n");
        }
}

