// This program is a part of NITAN MudLIB

#include <ansi.h>
#include <combat.h>

#define SHANG "「" HIG "达摩伤神剑" NOR "」"

inherit F_SSERVER;

string final(object me, object target, int damage);

int perform(object me, object target)
{
        object weapon;
        string msg;
        int ap, dp;
        int damage;

        if (userp(me) && ! me->query("can_perform/damo-jian/shang"))
                return notify_fail("你还没有受过高人指点，无法施展" SHANG "。\n");

        if (! target) target = offensive_target(me);

        if (! target || ! me->is_fighting(target))
                return notify_fail(SHANG "只能对战斗中的对手使用。\n");

        if (! objectp(weapon = me->query_temp("weapon")) ||
            (string)weapon->query("skill_type") != "sword")
                return notify_fail("你所使用的武器不对，难以施展" SHANG "。\n");

        if ((int)me->query_skill("damo-jian", 1) < 250)
                return notify_fail("你达摩剑法不够娴熟，难以施展" SHANG "。\n");

        if (me->query_skill_mapped("sword") != "damo-jian")
                return notify_fail("你没有激发达摩剑法，难以施展" SHANG "。\n");

        if ((int)me->query("max_neili") < 2000)
                return notify_fail("你的内力修为不够，难以施展" SHANG "。\n");

        if (me->query("neili") < 300)
                return notify_fail("你现在的真气不足，难以施展" SHANG "。\n");

        if (! living(target))
                return notify_fail("对方都已经这样了，用不着这么费力吧？\n");

        msg = HIG "$N" HIG "将手中" + weapon->name() +
              HIG "轻轻一振，剑脊叮叮作响，无形剑气直指$n"
              HIG "气海要穴。\n" NOR;

        ap = attack_power(me, "sword") + (int)me->query("int") * 20;
        dp = defense_power(target, "force") + (int)target->query("con") * 20;

        if (ap / 2 + random(ap) > dp)
        {
                damage = damage_power(me, "sword");
                msg += COMBAT_D->do_damage(me, target, WEAPON_ATTACK, damage, 55,
                                           (: final, me, target, damage :));
                me->start_busy(2);
                me->add("neili", -200);
        } else
        {
                msg += CYN "可是$n" CYN "内力深厚，使得$P"
                       CYN "这一招没有起到任何作用。\n" NOR;
                me->start_busy(3);
                me->add("neili", -100);
        }
        message_combatd(msg, me, target);

        return 1;
}

string final(object me, object target, int damage)
{
        int lvl = me->query_skill("damo-jian", 1);

        target->affect_by("damo_shangshen",
                ([ "level"    : lvl + random(lvl),
                   "id"       : me->query("id"),
                   "duration" : lvl / 50 + random(lvl / 20) ]));

        target->receive_damage("jing", damage / 2, me);
        target->receive_wound("jing", damage / 4, me);

        return HIR "结果$n" HIR "只觉气海穴上一痛，眼前一团"
               "黑，阵阵晕眩，难以继续战斗。\n" NOR;
}

