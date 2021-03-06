// This program is a part of NITAN MudLIB

#include <ansi.h>

#define LING "「" MAG "挪转乾坤" NOR "」"

void remove_effect(object me);

int perform(object me, object target)
{
        string msg;
        int level;
        
        if( me->query("family/family_name") != "明教" )
                return notify_fail("你不是明教弟子，无法施展" LING "。\n" NOR);

        if( !me->query("reborn/times") )        
                return notify_fail("你尚未转世重生，无法施展" LING "。\n" NOR);

        if( (level = me->query_skill("qiankun-danuoyi", 1)) < 1000 )
                return notify_fail("你的乾坤大挪移还不够熟练，难以施展" LING "。\n" NOR);

        if( (int)me->query("jingli") < 2000 )
                return notify_fail("你现在真气不足，难以施展" LING "。\n" NOR);

        if( (int)me->query("neili") < 5000 )
                return notify_fail("你现在内力不够，难以施展" LING "。\n" NOR);
                
        if (me->query_temp("nuozhuan"))
                return notify_fail("你已经运起" LING "。\n" NOR);

        me->add("neili", -1000);
        me->receive_damage("qi", 0);
        me->set_temp("nuozhuan", 1);
        msg = MAG "\n$N" MAG "提起真气，默念" LING + "心法，心中卸力拆招的法门已达发乎自然之境。\n" NOR;

        message_combatd(msg, me);
        
        me->start_call_out((: call_other, __FILE__, "remove_effect", me :), level/80);
        
        if( me->is_fighting() ) me->start_busy(2);
        return 1;

}

void remove_effect(object me)
{
        if ((int)me->query_temp("nuozhuan"))
        {
                me->delete_temp("nuozhuan");
                tell_object(me, "你的「挪转乾坤」运功完毕，将内力收回丹田。\n");
        }
}

