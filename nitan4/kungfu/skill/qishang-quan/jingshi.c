// jingshi.c 精失诀

#include <ansi.h>

inherit F_SSERVER;

int perform(object me)
{
        string msg,str;
        object target;
        int skill, jing_wound, eff_jing_wound, neili_wound;
        mixed ap, dp; 

        me->clean_up_enemy();
        target = me->select_opponent();

        skill = me->query_skill("qishang-quan",1) + me->query_skill("force",1);

        if( !me->is_fighting() )
                return notify_fail("「精失诀」只能在战斗中使用。\n");

        if( (int)me->query("neili") < 900 )
                return notify_fail("你的内力还不够高！\n");

        if( (int)me->query_skill("cuff") < 250 )
                return notify_fail("你的拳法还不到家，无法体现七伤拳的各种总诀！\n");

        if( (int)me->query_skill("qishang-quan", 1) < 250)
                return notify_fail("你七伤拳的修为不够，不能够体会精失诀! \n");

          if( (int)me->query_skill("force", 1) < 250)
                return notify_fail(HIM "你的基本内功修为不足，不能随便使用精失诀! \n" NOR);

        if( me->query_skill_mapped("cuff") != "qishang-quan")
                return notify_fail("你没有激发七伤拳，无法运用精失诀！\n");
        if (me->query_skill_prepared("cuff") != "qishang-quan")  
                return notify_fail("你没有准备使用七伤拳，无法施展「精失诀」。\n");  
        if( objectp(me->query_temp("weapon")) )
                return notify_fail("你必须空手才能使用此招！\n");


        msg = HIY "$N凝神定气，使出七伤拳总诀中的「" HIR "精失诀" HIY "」，双拳势如雷霆，向$n击去。\n"NOR;
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
                        me->add("neili",-300);

                msg = HIG "$N的拳只是轻轻的碰到了$n，但$N的真气趁这一瞬间已流入了$n体内！\n$n只觉得有点疲惫。。。\n"NOR;
                neili_wound = skill + random(skill);
                neili_wound += me->query("jiali");
                if(neili_wound > target->query("neili"))
                        neili_wound = target->query("neili");

                jing_wound = random((int)skill);
                jing_wound += me->query("jiali");
                eff_jing_wound = random((int)skill / 3);
                eff_jing_wound += (int)me->query("jiali")/2;
                target->receive_damage("jing", jing_wound, me);
                target->receive_wound("jing", eff_jing_wound, me);
		str = COMBAT_D->status_msg((int)target->query("qi") * 100 /(int)target->query("max_qi"));
		msg += "($n"+str+")\n";
                me->start_busy(2);
                if (! target->is_busy())
                target->start_busy(1 + random(2));
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

