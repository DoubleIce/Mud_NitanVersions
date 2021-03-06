// This program is a part of NITAN MudLIB
// lian.c 莲花指

#include <ansi.h>

inherit F_SSERVER;

int perform(object me, object target)
{
	object weapon;
	string msg;
        int ap, dp;
        int skill;

        if (userp(me) && ! me->query("can_perform/canhe-zhi/lian"))
                return notify_fail("你还没有受过高人指点，无法施展。\n");
                
        if (! target)
        {
                me->clean_up_enemy();
                target = me->select_opponent();
        }

        if (! me->is_fighting(target))
                return notify_fail("「莲花指」只能对战斗中的对手使用。\n");

	if (target->is_busy())
		return notify_fail(target->name() + "目前正自顾不暇，放胆攻击吧！\n");

        skill = me->query_skill("canhe-zhi", 1);

        if (skill < 80)
                return notify_fail("你的参合指修为有限, 不能使用「莲花指」！\n");

        if (me->query("neili") < 70)
                return notify_fail("你的真气不够，无法运用「莲花指」！\n");

        if (me->query_skill_mapped("finger") != "canhe-zhi")
                return notify_fail("你没有激发参合指, 不能使用「莲花指」！\n");

        msg = HIC "$N" HIC "五指伸出，宛若一朵盛开的莲花，轻飘飘的拂向$n"
              HIC "。\n" NOR;

        me->add("neili", -30);
        ap = attack_power(me, "finger");
        dp = defense_power(target, "dodge");
	if (ap / 2 + random(ap) > dp)
        {
		msg += HIR "结果$p" HIR "被$P"
                       HIR "逼得招架不迭，无暇旁顾。\n" NOR;
                target->start_busy(random(4) + 2);
	} else
        {
		msg += CYN "可是$p" CYN "看破了$P"
                       CYN "的企图，轻轻一跃，躲开了这一招。\n" NOR;
                me->start_busy(2);
	}
	message_combatd(msg, me, target);

	return 1;
}

