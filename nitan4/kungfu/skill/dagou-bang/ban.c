// This program is a part of NITAN MudLIB

#include <ansi.h>
#include <combat.h>

#define BAN "「" HIG "绊字诀" NOR "」"

inherit F_SSERVER;

int perform(object me, object target)
{
        object weapon;
        string msg;
        int ap, dp, damage, level;

        if (userp(me) && ! me->query("can_perform/dagou-bang/ban"))
                return notify_fail("你还没有受过高人指点，无法施展" BAN "。\n");

        if (! target) target = offensive_target(me);

        if (! target || ! me->is_fighting(target))
                return notify_fail(BAN "只能对战斗中的对手使用。\n");

        if (! objectp(weapon = me->query_temp("weapon")) ||
            (string)weapon->query("skill_type") != "staff")
                return notify_fail("你使用的武器不对，难以施展" BAN "。\n");

        level = me->query_skill("dagou-bang", 1);

        if (level < 180)
                return notify_fail("你打狗棒法不够娴熟，难以施展" BAN "。\n");

        if (me->query_skill_mapped("staff") != "dagou-bang")
                return notify_fail("你没有激发打狗棒法，难以施展" BAN "。\n");

        if ((int)me->query_skill("force") < 240)
                return notify_fail("你的内功火候不足，难以施展" BAN "。\n");

        if (me->query("neili") < 300)
                return notify_fail("你现在的真气不够，难以施展" BAN "。\n");

        if (! living(target))
                return notify_fail("对方都已经这样了，用不着这么费力吧？\n");

        msg = HIG "$N" HIG "使出打狗棒法「" NOR + WHT "绊"
              HIG "」字诀，手中" + weapon->query("name") +
              HIG "左封右逼，缓缓朝$n" HIG "挑去。\n" NOR;

        ap = attack_power(me, "staff") + me->query_int();
        dp = defense_power(target, "dodge") + target->query_dex();

        if (ap / 2 + random(ap) > dp)
        {
                if (me->query("max_neili") > target->query("max_neili") * 3)
                {       
                        msg += HIR "$n" HIR "全身一颤，立足不稳，被$N"
                                HIR "这招击得飞起，重重的跌落在地上。\n" NOR;

                        me->add("neili", -50);
                        me->start_busy(1);

                        message_combatd(msg, me, target);
                        target->receive_damage("qi", 100, me);
                        target->set("eff_qi", 1);
                        target->set("eff_jing", 1);
                        target->unconcious();
                        return 1;
                } else
                {
                        damage = damage_power(me, "staff");
                        msg += COMBAT_D->do_damage(me, target, WEAPON_ATTACK, damage, 55,
                                           HIR "只听$n" HIR "小腿处「嗤嗤」两声脆"
                                           "响，竟被$N" HIR "的" + weapon->name() +
                                           HIR "贯出两个血洞。\n" NOR);
                        me->start_busy(3);
                        me->add("neili", -200);
                }
        } else
        {
                msg += CYN "可$n" CYN "全神防御，不露半点破绽，使得$N"
                       CYN "这招无功而返。\n" NOR;
                me->start_busy(4);
                me->add("neili", -100);
        }
        message_combatd(msg, me, target);

        return 1;
}

