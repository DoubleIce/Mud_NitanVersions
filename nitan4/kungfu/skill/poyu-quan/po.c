// This program is a part of NITAN MudLIB
// poshi.c 破石一击

#include <ansi.h>
#include <combat.h>

inherit F_SSERVER;

#define PO "「" HIW "破石一击" NOR "」"

int perform(object me, object target)
{
        object weapon;
        int damage;
        string msg;
        int ap, dp;

        if (! target)
        {
                me->clean_up_enemy();
                target = me->select_opponent();
        }

        if (userp(me) && ! me->query("can_perform/poyu-quan/po"))
                return notify_fail("你还没有受过高人指点，无法施展" PO "。\n"); 

        if (! target || ! me->is_fighting(target))
                return notify_fail(PO "只能对战斗中的对手使用。\n");

        if ((int)me->query_skill("poyu-quan", 1) < 140)
                return notify_fail("你的劈石破玉拳不够娴熟，无法施展" PO "。\n");
                                
        if ((int)me->query_skill("force", 1) < 120)
                return notify_fail("你的内功修为还不够，无法施展" PO "\n");
                        
        if ((int)me->query("neili") < 300)
                return notify_fail("你现在真气不够，无法施展" PO "。\n");

        if (me->query_skill_prepared("cuff") != "poyu-quan")
                return notify_fail("你没有准备使用劈石破玉拳，无法施展" PO "。\n");

       if (! living(target))
              return notify_fail("对方都已经这样了，用不着这么费力吧？\n");

        msg = HIY "$N" HIY "大喝一声，拳头如闪电一般重重的击向$n" HIY "。\n"NOR;

        ap = attack_power(me, "cuff") + me->query_str();

        dp = defense_power(target, "parry") + target->query_str();
             
        if (ap / 2 + random(ap) > dp)
        {
                damage = damage_power(me, "cuff");

                me->add("neili", -220);
                msg += COMBAT_D->do_damage(me, target, UNARMED_ATTACK, damage, 55,
                                           HIR "只见$P" HIR "这一拳把$p" HIR
                                           "飞了出去，重重的摔在地上，吐血不止！\n" NOR);
                me->start_busy(2);
        } else 
        {
                msg += HIC "可是$p" HIC "奋力招架，硬生生的挡开了$P"
                       HIC "这一招。\n"NOR;
                me->add("neili", -120);
                me->start_busy(3);
        }
        message_combatd(msg, me, target);

        return 1;
}

