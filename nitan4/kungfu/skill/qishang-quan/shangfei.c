// shangfei.c 伤肺诀

#include <ansi.h>

inherit F_DBASE;
inherit F_SSERVER;

private void remove_effect(object me, int amount);

int perform(object me)
{
        string msg;
        object target;
        int skill, dodge_decrease;
        mixed ap, dp; 

        me->clean_up_enemy();
        target = me->select_opponent();

        skill = me->query_skill("qishang-quan",1) + me->query_skill("force",1);

        if( !me->is_fighting() )
                return notify_fail("「伤肺诀」只能在战斗中使用。\n");

        if( (int)me->query("neili") < 600 )
                return notify_fail("你的内力还不够高！\n");

        if( (int)me->query_skill("cuff") < 60 )
                return notify_fail("你的拳法还不到家，无法体现七伤拳的各种总诀！\n");

        if( (int)me->query_skill("qishang-quan", 1) < 60)
                return notify_fail("你七伤拳的修为不够，不能够体会伤肺诀! \n");

        if( (int)me->query_skill("force", 1) < 60)
                  return notify_fail(HIM "你的基本内功修为不足，不能随便使用伤肺诀! \n" NOR);

        if( me->query_skill_mapped("cuff") != "qishang-quan")
                return notify_fail("你没有激发七伤拳，无法运用伤肺诀！\n");
        if (me->query_skill_prepared("cuff") != "qishang-quan")  
                return notify_fail("你没有准备使用七伤拳，无法施展「伤肺诀」。\n");  
        if( objectp(me->query_temp("weapon")) )
                return notify_fail("你必须空手才能使用此招！\n");


        msg = HIY "$N凝神定气，使出七伤拳总诀中的「" HIR "伤肺诀" HIY "」，双拳势如雷霆，向$n击去。\n"NOR;
        message_vision(msg, me, target);

                   ap = count_add(me->query("combat_exp"), count_mul(skill, 500));  
                   ap = atoi(count_div(ap, 100));  
                   dp = count_div(target->query("combat_exp"), 2);  
                   dp = atoi(count_div(dp, 100));  
        if( dp < 1 )
                dp = 1;
        if( random(ap) > dp || !living(target))
        {
                if(userp(me))
                        me->add("neili",-100);

                msg = HIG "$N的拳风隐含风雷，“澎”的一声打在$n身上！\n$n只觉得呼吸不顺，顿时脚步慢了许多！\n"NOR;
                dodge_decrease = (int)target->query("apply/dodge") / 10;
                target->add_temp("apply/dodge", -dodge_decrease);
                target->start_busy(2);
                me->start_busy(2 + random(2));
                call_out("remove_effect", skill/40, target, dodge_decrease);
        }
        else
        {
                msg = HIG "只见$n不慌不忙，轻轻一闪，躲过了$N的必杀一击！\n"NOR;
                if(userp(me))
                        me->add("neili",-100);
                me->start_busy(3);
        }
        message_vision(msg, me, target);

        return 1;
}

private void remove_effect(object me, int amount)
{
        if (!me)
                return;
        me->add_temp("apply/dodge", amount);
        tell_object(me, "你感觉呼吸变得顺畅，所中的七伤拳伤肺劲气逐渐消解了。\n");
}
