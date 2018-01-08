// tui.c 推

#include <ansi.h>
#include <combat.h>

inherit F_SSERVER;

int perform(object me, object target)
{
        string msg;
        int skill, ap, dp, damage;

        if (! target || target == me)
        {
                me->clean_up_enemy();
                target = me->select_opponent();
        }

        if (! target || ! me->is_fighting(target))
                return notify_fail("蛤蟆功「推天式」只能对战斗中的对手使用。\n");

        if ( objectp(me->query_temp("weapon")) )
                 return notify_fail("你手持兵器，无法施展蛤蟆功的掌法绝技。\n");

        skill = me->query_skill("hamagong", 1);

        if (skill < 240)
                return notify_fail("你的蛤蟆功修为不够精深，不能使用「推天式」！\n");

        if (me->query("max_neili") < 4000)
                return notify_fail("你的内力修为不够深厚，无法施展「推天式」！\n");

        if (me->query("neili") < 800)
                return notify_fail("你的真气不够，无法运用「推天式」！\n");

        msg = HIY "$N" HIY "蹲在地上，“嗝”的一声大叫，双手弯"
              "与肩齐，平推而出，一股极大的力道如同"
              "排山倒海一般奔向$n" HIY "。\n" NOR;

        ap = me->query_skill("force") * 15 + me->query("max_neili");
        if (living(target))
                dp = target->query_skill("force") * 15 + target->query("max_neili") +
                     target->query_skill("yiyang-zhi", 1) * 20;
        else    dp = 1;

        if (ap / 2 + random(ap) > dp)
        {
                me->add("neili", -400);
                me->start_busy(2);
                target->start_busy(1);
                damage = (ap - dp) / 10 + random(ap / 10);
                msg += COMBAT_D->do_damage(me, target, REMOTE_ATTACK, damage, 50,
                                           HIR "$n" HIR "奋力低档，但是$P" HIR "的来势何"
                                           "等浩大，$p" HIR "登时觉得气血不畅，“哇”的"
                                           "吐出了一口鲜血。\n" NOR);
        } else
        if (target->query_skill("yiyang-zhi", 1))
        {
                me->add("neili", -300);
                msg += HIG "然而$p" HIG "哈哈一笑，随手一指刺出，正是一"
                       "阳指的精妙招数，轻易的化解了$P" HIG "的攻势。\n" NOR;
        } else
        {
                me->add("neili",-200);
                msg += CYN "可是$n" CYN "将内力运到双臂上，接下了$P"
                       CYN "这一推之式，只听“蓬”的一声，震得四周"
                       "尘土飞扬。\n" NOR;
                me->start_busy(3);
                target->start_busy(2);
                if (target->query("neili") > 200)
                        target->add("neili", -200);
                else
                        target->set("neili", 0);
        }
        message_combatd(msg, me, target);

        return 1;
}

