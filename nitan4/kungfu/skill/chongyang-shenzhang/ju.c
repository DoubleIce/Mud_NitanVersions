// This program is a part of NITAN MudLIB

#include <ansi.h>
#include <combat.h>

#define JU "「" HIW "三花聚顶" NOR "」"

inherit F_SSERVER;

int perform(object me, object target)
{
        object weapon;
        int damage;
        string msg;
        int ap, dp;

        /*
        if (userp(me) && ! me->query("can_perform/chongyang-shenzhang/ju"))
                return notify_fail("你还没有受过高人指点，无法施展" JU "。\n");
        */
        
        if (! target)
        {
                me->clean_up_enemy();
                target = me->select_opponent();
        }

        if (! target || ! me->is_fighting(target))
                return notify_fail(JU "只能对战斗中的对手使用。\n");
 
        if (objectp(me->query_temp("weapon")))
                return notify_fail(JU "只能空手施展。\n");

        if ((int)me->query_skill("chongyang-shenzhang", 1) < 120)
                return notify_fail("你的重阳神掌不够娴熟，难以施展" JU "。\n");

        if ((int)me->query_skill("force") < 180)
                return notify_fail("你的内功修为不够，难以施展" JU "。\n");

        if (me->query_skill_mapped("strike") != "chongyang-shenzhang")
                return notify_fail("你没有激发重阳神掌法，难以施展" JU "。\n");

        if (me->query_skill_prepared("strike") != "chongyang-shenzhang")
                return notify_fail("你没有准备重阳神掌法，难以施展" JU "。\n");

        if ((int)me->query("neili") < 300)
                return notify_fail("你现在的真气不足，难以施展" JU "。\n");

        if (! living(target))
                return notify_fail("对方都已经这样了，用不着这么费力吧？\n");

        msg = HIY "$N" HIY "大喝一声，合身向$n" HIY "扑上，双掌同时"
              "击出，正是一招「" HIW "三花聚顶" HIY "」。\n" NOR;

        ap = attack_power(me, "strike");
        dp = defense_power(target, "force");
             
        if (ap / 2 + random(ap) > dp)
        {
                me->start_busy(2);
                me->add("neili", -200);
                damage = damage_power(me, "strike");
                msg += COMBAT_D->do_damage(me, target, UNARMED_ATTACK, damage, 50,
                                           HIR "结果$p" HIR "被$P" HIR "的气势所"
                                           "摄，慌忙后退，却被$P" HIR "一掌击个正"
                                           "中，吐血不止！\n" NOR);
        } else
        {
                me->start_busy(3);
                me->add("neili", -60);
                msg += CYN "可是$p" CYN "识破了$P"
                       CYN "这一招，斜斜一跃避开。\n" NOR;
        }
        message_combatd(msg, me, target);

        return 1;
}
