// This program is a part of NITAN MudLIB

#include <ansi.h>
#include <combat.h>

inherit F_SSERVER;

int perform(object me, object target)
{
	object weapon;
	int damage;
	string msg;
	int ap, dp;

        if (userp(me) && ! me->query("can_perform/liancheng-jianfa/erguang"))
                return notify_fail("你还没有受过高人指点，无法施展「耳光式」。\n");

	if( !target ) target = offensive_target(me);

	if( !target || !target->is_character() || !me->is_fighting(target) )
		return notify_fail("「耳光式」只能对战斗中的对手使用。\n");

	if (!objectp(weapon = me->query_temp("weapon"))
	|| (string)weapon->query("skill_type") != "sword")
		return notify_fail("你使用的武器不对。\n");
		
	if( (int)me->query_skill("liancheng-jianfa", 1) < 70 )
		return notify_fail("你的连城剑法不够娴熟，不会使用。\n");
	                        
	if( (int)me->query_skill("force", 1) < 70 )
		return notify_fail("你的基本内功不够高。\n");
			
	if( (int)me->query("neili", 1) < 300 )
		return notify_fail("你现在内力太弱，不能使用「耳光式」。\n");
			
	msg = HBYEL "只见$N手中兵器由右手快速交换到左手，右手以意想不到的方位挥向$n的脸颊。\n"NOR;

        ap = attack_power(me, "sword");
        dp = defense_power(target, "force");

        if (ap / 2 + random(ap) > dp)
	{	
		damage = damage_power(me, "sword");

                msg += COMBAT_D->do_damage(me, target, WEAPON_ATTACK, damage, 50,
                                           CYN "$n只觉只觉得脸上一正火辣辣的生痛，"
                                           "已被$N响亮的打了一耳光！\n" NOR);	

		me->add("neili", -200);
		me->start_busy(2);
	} else 
	{
		msg += CYN "可是$p身形一侧,躲过了$P的掌风。\n" NOR;
		me->add("neili", -100);
		me->start_busy(3);
	}
	message_combatd(msg, me, target);

	return 1;
}
