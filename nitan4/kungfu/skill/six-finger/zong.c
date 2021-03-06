#include <ansi.h>
#include <combat.h>

inherit F_SSERVER;

#define ZONG "「" HIM "纵横天下" NOR "」"

int perform(object me, object target)
{
        string msg;
        int ap, dp;
        int damage, skill;

        if (! target) target = offensive_target(me);
        
        /*
        if (userp(me) && ! me->query("can_perform/six-finger/zong"))
                return notify_fail("你所使用的外功中没有这种功能。\n");
        */
        
        if (! target || ! me->is_fighting(target))
                return notify_fail(ZONG "只能对战斗中的对手使用。\n");

        if (me->query_skill_prepared("finger") != "six-finger")
                return notify_fail("你没有准备使用六脉神剑，无法施展" ZONG "。\n");

        skill = me->query_skill("six-finger", 1);

        if (skill < 260)
                return notify_fail("你的六脉神剑修为有限，无法使用" ZONG "！\n");

        if (me->query_skill("force") < 480)
                return notify_fail("你的内功火候不够，难以施展" ZONG "！\n");

        if (me->query("max_neili") < 5500)
                return notify_fail("你的内力修为不够,无法施展" ZONG "！\n");

        if (me->query("neili") < 850)
                return notify_fail("你的真气不够，现在无法施展" ZONG "！\n");

        if (me->query_temp("weapon"))
                return notify_fail("你必须是空手才能施展" ZONG "！\n");

        if (! living(target))
                return notify_fail("对方都已经这样了，用不着这么费力吧？\n");


        msg = HIM "$N" HIM "一声清啸，十指纷弹，顿觉六脉剑谱已涌上心头，此起"
              "彼伏、连绵不绝。霎时剑气如奔，连绵无尽的万道剑气豁然贯向$n" HIM 
              "！\n" NOR;

        ap = attack_power(me, "finger") + me->query_skill("force");
        dp = defense_power(target, "dodge") + target->query_skill("force");

        if (target->query_skill("martial-cognize", 1) >= 800
            && random (100) == 1 )
        {
                me->add("neili", -600);
                me->start_busy(3);
                msg += HIY "但见$n" HIY "会心一笑，轻拂衣袖，轻易的躲过这一招！\n"NOR;
        } else
        if (ap / 2 + random(ap) > dp)
        { 
                damage = damage_power(me, "finger");
                me->add("neili", -800);
                msg += COMBAT_D->do_damage(me, target, SPECIAL_ATTACK, damage, 85,
                                           HIR "只听$n" HIR "一声惨叫，万道剑气已"
                                           "透体而过，伤口处鲜血顿时狂涌，痛苦难当！\n" NOR);
                me->start_busy(2);
        } else
        {
                me->add("neili", -400);
                me->start_busy(3);
                msg += CYN "$n" CYN "见$N" CYN "来势汹涌，不敢轻易"
                       "招架，急忙提气跃开。\n" NOR;
        }
        message_sort(msg, me, target);

        return 1;
}


