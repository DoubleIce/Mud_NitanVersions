// This program is a part of NITAN MudLIB
// shentong.c 先天功 纯阳神通功

// This program is a part of NITAN MudLIB

#include <ansi.h>
#include <combat.h>

#define FEN "「" HIW "纯阳神通功" NOR "」"

inherit F_SSERVER;

int perform(object me, object target)
{
        object weapon;
        int ap, dp, damage;
        string msg;

        if (userp(me) && ! me->query("can_perform/xiantian-gong/shen"))
                return notify_fail("你未得高人指点，不知该如何施展" FEN "。\n"); 

        if (! target) target = offensive_target(me);

        if (! target || ! me->is_fighting(target))
                return notify_fail(FEN "只能对战斗中的对手使用。\n");

        if (me->query_temp("weapon") || me->query_temp("secondary_weapon"))
                return notify_fail(FEN "只能空手施展。\n");

        if ((int)me->query_skill("xiantian-gong", 1) < 240)
                return notify_fail("你的先天功修为不够，难以施展" FEN "。\n");

        if (me->query("max_neili") < 4000)
                return notify_fail("你的内力修为不足，难以施展" FEN "。\n");

        if (me->query_skill_mapped("unarmed") != "xiantian-gong")
                return notify_fail("你没有激发先天功为拳脚，难以施展" FEN "。\n");

        if (me->query_skill_mapped("force") != "xiantian-gong")
                return notify_fail("你没有激发先天功为内功，难以施展" FEN "。\n");

        if (me->query_skill_prepared("unarmed") != "xiantian-gong")
                return notify_fail("你没有准备使用先天功，难以施展" FEN "。\n");

        if (me->query("neili") < 1000)
                return notify_fail("你现在的真气不足，难以施展" FEN "。\n");

        if (! living(target))
                return notify_fail("对方都已经这样了，用不着这么费力吧？\n");

        msg = HIW "$N" HIW "运起纯阳神通功，片刻便见白气逐渐笼罩全身，双眼精光四射，与平时判若两人。\n"
              HIW "$N" HIW "接着突然出掌攻向$n，当真是无声无息，却迅如闪电。\n" NOR;       

        ap = attack_power(me, "unarmed") + me->query_skill("force");
        dp = defense_power(target, "dodge") + target->query_skill("force");

        if (ap / 2 + random(ap) > dp)
        {
                damage = 0;
                if (me->query("max_neili") > target->query("max_neili") * 2)
                {
                        me->start_busy(2);
                        msg += HIR "$n" HIR "来不及反应，即被$N纯阳神通功惊人神功击中。\n" NOR "( $n"
                               RED "受伤过重，已经有如风中残烛，随时都可能断气"
                               "。" NOR ")\n";
                        damage = -1;
                } else
                {
                        me->start_busy(3);
                        damage = damage_power(me, "unarmed");
                        me->add("neili", -500);
                        msg += COMBAT_D->do_damage(me, target, REMOTE_ATTACK, damage, 80,
                                                   HIR "结果$N" HIR "纯阳神通功正中$n" HIR "胸"
                                                   "口，纯阳神通功登时透胸而入，$n" HIR "接连喷出数"
                                                   "口鲜血。\n" NOR);
                }
        } else
        {
                me->start_busy(5);
                me->add("neili", -120);
                msg += CYN "可是$p" CYN "识破了$P"
                       CYN "这一招，但却很狼狈的躲避开来。\n" NOR;
        }
        message_combatd(msg, me, target);

        if (damage < 0)
                target->die(me);

        return 1;
}
