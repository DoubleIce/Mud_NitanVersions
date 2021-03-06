// This program is a part of NITAN MudLIB

#include <ansi.h>
#include <combat.h>

#define SHI "「" HIR "噬血穹苍" NOR "」"

inherit F_SSERVER;
 
int perform(object me, object target)
{
        object weapon;
        string msg;
        int ap, dp, damage;
        int i, count;

        if (userp(me) && ! me->query("can_perform/xuedao-daofa/shi"))
                return notify_fail("你还没有受过高人指点，无法施展" SHI "。\n");

        if (! target)
        {
                me->clean_up_enemy();
                target = me->select_opponent();
        }

        if (! target || ! me->is_fighting(target))
                return notify_fail(SHI "只能对战斗中的对手使用。\n");
 
        if (! objectp(weapon = me->query_temp("weapon")) ||
            (string)weapon->query("skill_type") != "blade")
                return notify_fail("你使用的武器不对，难以施展" SHI "。\n");

        if ((int)me->query_skill("force") < 250)
                return notify_fail("你的内功火候不够，难以施展" SHI "。\n");

        if ((int)me->query_skill("xuedao-daofa", 1) < 180)
                return notify_fail("你的血刀大法还不到家，难以施展" SHI "。\n");

        if (me->query_skill_mapped("blade") != "xuedao-daofa")
                return notify_fail("你没有激发血刀大法为刀法，难以施展" SHI "。\n");

        if ((int)me->query("qi") < 100)
                return notify_fail("你目前气血翻滚，难以施展" SHI "。\n");

        if ((int)me->query("neili") < 500)
                return notify_fail("你目前真气不足，难以施展" SHI "。\n");

        if (! living(target))
                return notify_fail("对方都已经这样了，用不着这么费力吧？\n");

        ap = attack_power(me, "blade") + me->query_str() * 20;
        dp = defense_power(target, "dodge") + target->query_dex() * 20;
             
        msg = HIY "$N" HIY "陡然施出「" HIR "噬血穹苍" HIY "」，手中" +
              weapon->name() + HIY "腾起无边杀意，携着风雷之势向$n" HIY
              "劈斩而去！\n"NOR;

        if (ap / 2 + random(ap) > dp)
        {
                damage = damage_power(me, "blade");
                msg += COMBAT_D->do_damage(me, target, SPECIAL_ATTACK, damage, 75,
                                           HIR "$n" HIR "只觉眼前一蓬血雨喷洒而出"
                                           "，已被$N" HIR "这一刀劈了个正中。\n" NOR);
        } else
        {
                msg += CYN "$p" CYN "只见$P" CYN "来势汹涌，难以抵挡，当"
                       "即飞身朝后跃出数尺。\n" NOR;
        }

        msg += HIY "\n紧接着$N" HIY "嗔目大喝，手中" + weapon->name() +
               HIY "一振，迸出漫天血光，铺天盖地洒向$n" HIY "！\n"NOR;

        ap = attack_power(me, "blade");
        dp = defense_power(target, "parry");
        if (ap / 2 + random(ap) > dp)             
        {
                msg += HIR "霎时间$n" HIR "只觉周围杀气弥漫，全身气血翻"
                       "滚，甚难招架。\n" NOR;
                count = me->query_skill("xuedao-daofa", 1) / 4;
        } else
        {
                msg += HIY "霎时间$n" HIY "只觉周围杀气弥漫，心底微微一"
                       "惊，连忙奋力招架。\n" NOR;
                count = 0;
        }
        message_combatd(msg, me, target);

        me->add_temp("apply/attack", count);
        me->add_temp("apply/damage", count);

        for (i = 0; i < 6; i++)
        {
                if (! me->is_fighting(target))
                        break;

                if (random(3) == 1 && ! target->is_busy())
                        target->start_busy(1);

                COMBAT_D->do_attack(me, target, weapon, 0);
        }
        // me->receive_wound("qi", 80);
        me->add_temp("apply/attack", -count);
        me->add_temp("apply/damage", -count);
        me->start_busy(3 + random(4));
        me->add("neili", -200 - random(300));
        return 1;
}

