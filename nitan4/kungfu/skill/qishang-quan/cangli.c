// cangli.c 藏离诀

#include <ansi.h>

inherit F_SSERVER;

int perform(object me)
{
        string msg,str;
        object target;
        int skill, neili_wound;
        mixed ap, dp;

        me->clean_up_enemy();
        target = me->select_opponent();

        skill = me->query_skill("qishang-quan",1) + me->query_skill("force",1);

        if( !me->is_fighting() )
                return notify_fail("「藏离诀」只能在战斗中使用。\n");

        if( (int)me->query("neili") < 800 )
                return notify_fail("你的内力还不够高！\n");

        if( (int)me->query_skill("cuff") < 220 )
                return notify_fail("你的拳法还不到家，无法体现七伤拳的各种总诀！\n");

        if( (int)me->query_skill("qishang-quan", 1) < 220)
                return notify_fail("你七伤拳的修为不够，不能够体会藏离诀! \n");

        if( (int)me->query_skill("force", 1) < 220)
                return notify_fail(HIM "你的基本内功修为不足，不能随便使用藏离诀! \n" NOR);

        if( me->query_skill_mapped("cuff") != "qishang-quan")
                return notify_fail("你没有激发七伤拳，无法运用藏离诀！\n");
        if (me->query_skill_prepared("cuff") != "qishang-quan")  
                return notify_fail("你没有准备使用七伤拳，无法施展「藏离诀」。\n");  
        if( objectp(me->query_temp("weapon")) )
                return notify_fail("你必须空手才能使用此招！\n");


        msg = HIY "$N凝神定气，使出七伤拳总诀中的「" HIR "藏离诀" HIY "」，双拳势如雷霆，向$n击去。\n"NOR;
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
                        me->add("neili",-200);

                msg = HIG "$n被$N拳风扫中，只觉全身真气失却驾驭，往外急泻！\n"NOR;
                neili_wound = skill + random(skill * 2);
                neili_wound += me->query("jiali");
                if(neili_wound > target->query("neili"))
                        neili_wound = target->query("neili");
                if(target->query("neili")<0)
                        neili_wound = 0;
                target->add("neili", -neili_wound);
                target->receive_wound("qi", neili_wound, me);
                target->start_busy(2);
                me->start_busy(2 + random(2));
		str = COMBAT_D->status_msg((int)target->query("qi") * 100 /(int)target->query("max_qi"));
		msg += "($n"+str+")\n";
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

