// poli.c 破立

#include <ansi.h>
#include <combat.h>

inherit F_SSERVER;
int perform(object me, object target)
{
	object weapon;
	string msg;
        int ap, dp;
	int damage;

        if (userp(me) && ! me->query("can_perform/riyue-lun/poli"))
                return notify_fail("你还不会运用「破立」这一绝技。\n");

	if (! target ) target = offensive_target(me);

	if (! target || ! me->is_fighting(target))
		return notify_fail("「破立」只能对战斗中的对手使用。\n");

	if (! objectp(weapon = me->query_temp("weapon")) ||
	    (string)weapon->query("skill_type") != "hammer")
		return notify_fail("你使用的武器不对。\n");

	if ((int)me->query_skill("riyue-lun", 1) < 120)
		return notify_fail("你的日月轮法还不够娴熟，不会使用「破立」。\n");

        if ((string)me->query_skill_mapped("force") != "longxiang-gong")
                return notify_fail("你必须激发龙象般若功才能施展出「破立」！\n");
        
	if ((int)me->query_skill("force") < 180)
		return notify_fail("你的内功不够深厚，无法施展「破立」！\n");

        if (me->query("neili") < 400)
                return notify_fail("你的真气不够，无法施展「破立」！\n");

        if (me->query_skill_mapped("hammer") != "riyue-lun")
                return notify_fail("你没有激发日月轮法，无法施展「破立」！\n");

	msg = HIY "$N" HIY "手举" + weapon->name() + "，奋力向$n" +
              HIY "砸下，气浪迭起，全然把$n" HIY "卷在其中！\n";

        ap = attack_power(me, "force") + me->query("str") * 15;
        dp = defense_power(target, "force") + target->query("str") * 10;

	if (dp < 1) dp = 1;
        if (ap / 2 + random(ap) > dp || !living(target))
	{
		me->add("neili", -300);
		damage = ap / 2 + random(ap / 2);
                msg += COMBAT_D->do_damage(me, target, WEAPON_ATTACK, damage, 50,
                                           HIR "$n" HIR "被$N" HIR "这强悍无比的内劲冲击"
                                           "得左摇右慌，接连中招，狂喷鲜血。\n" NOR);
		me->start_busy(2);

	} else
	{
		msg += HIC "却见$p" HIC "浑不在意，轻轻一闪就躲过了$P"
		       HIC "的凶悍招数！\n"NOR;
		me->add("neili", -150);
		me->start_busy(3);
	}
	message_combatd(msg, me, target);

	return 1;
}
