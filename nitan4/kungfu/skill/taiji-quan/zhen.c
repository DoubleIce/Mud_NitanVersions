// zhen.c 太极拳「震」字诀

#include <ansi.h>
#include <combat.h>

#define PFM_NAME        "震字诀"

inherit F_SSERVER;

int perform(object me, object target)
{
	int damage;
	string msg;
        int ap, dp;
        string force;

        if (userp(me) && ! me->query("can_perform/taiji-quan/zhen"))
                return notify_fail("你还没有受过高人指点，无法施展「" PFM_NAME "」。\n");
                        
        if(! target) target = offensive_target(me);

        if(! target || ! target->is_character() || ! me->is_fighting()) 
		return notify_fail("「" + PFM_NAME + "」只能对战斗中的对手使用。\n");

	if(objectp(me->query_temp("weapon")))
		return notify_fail("你必须空手才能使用「" + PFM_NAME + "」。\n");		
		
        if((int)me->query_skill("taiji-quan", 1) < 180)
		return notify_fail("你的太极拳不够娴熟，不会使用「" + PFM_NAME + "」。\n");
	                        
        if((int)me->query_skill("force", 1) < 200)
		return notify_fail("你的内功不够高，不能用来反震伤敌。\n");
			
        if((int)me->query("neili") < 1000)
		return notify_fail("你现在内力太弱，震也震不伤敌人。\n");
			
        msg = HIY "$N" HIY "默运神功，真气流转，双手左右连画，一个圆圈已将$n"
              HIY "套住，\n太极拳中的「" HIW + PFM_NAME + HIY "」信手使出，一道"
              HIY "浑厚的内力向$n" HIY "推去！\n" NOR;

        ap = attack_power(me, "cuff") + me->query_skill("force");
        dp = defense_power(target, "parry") + target->query_skill("force");
             
        if (ap / 2 + random(ap) > dp)
        {
                if (me->query("neili") < target->query("neili"))
                {
                        damage = damage_power(me, "cuff");

                        msg += COMBAT_D->do_damage(me, target, UNARMED_ATTACK, damage, 60,
                                                   HIC "\n眼见$P" HIC "就要将$p震倒，突然，$n"
                                                   HIC "运起全身内力，强忍疼痛硬接了$P一招。\n" NOR);
                        if (! target->is_busy())
                        target->start_busy(3);
                        me->start_busy(3);
                        target->add("neili", -(target->query("neili") / 2));
                        me->add("neili", -(me->query("neili") / (2 + random (2))));
                }
                else
                {
                        damage = damage_power(me, "cuff");

                        msg += COMBAT_D->do_damage(me, target, UNARMED_ATTACK, damage, 100,
                                                   HIC "\n眼见$n" HIC "被$P的内力压得透不过起来，只听得$N"
                                                   HIC "“砰”的一声击中$n" HIC "，$p全身骨骼便似散了"
                                                   HIC "架一般倒了下去。\n" NOR);
                        me->start_busy(3);
                        target->start_busy(1);
                        me->add("neili", -(me->query("neili") / (2 + random (3))));
                }
        }
        else
        {
                msg += HIG "\n可$p竟随手便把$P汇聚全身功力的招数架开，吓得$P手足无措！\n" NOR;
                me->add("neili", -100);
                me->start_busy(3);
        }
        message_combatd(msg, me, target, 0, 1);
	return 1;
}
