#include <ansi.h>
#include <combat.h> 

inherit F_SSERVER;
int perform(object me, object target)
{
        int damage;
        string msg;
	int ap,dp;

        if( !target ) target = offensive_target(me);

        if( !target || !target->is_character() || !me->is_fighting(target) )
                return notify_fail("六脉归宗只能对战斗中的对手使用。\n");

              if (me->query_skill_mapped("finger") != "six-finger") 
                      return notify_fail("你没有激发六脉神剑，无法施展「六脉归宗」。\n"); 

        if( objectp(me->query_temp("weapon")) )
                return notify_fail("你必须空手才能使用六脉归宗！\n");
             
        if( (int)me->query_skill("six-finger", 1) < 200 )
             return notify_fail("你的六脉神剑不够娴熟，不会使用六剑归宗。\n");
              
        if( (int)me->query("max_neili", 1) < 8000 )
                return notify_fail("你现在内力不够深厚，不能使用六剑齐发。\n");
                        
        if( (int)me->query("neili", 1) < 1500 )
           return notify_fail("你现在内力太弱，不能使用六剑归宗！\n");

              if (me->query_skill_prepared("finger") != "six-finger") 
                      return notify_fail("你没有准备使用六脉神剑，无法施展「六脉归宗」。\n"); 

        msg = HIY
"$N使出六脉神剑最强绝技『六脉归宗』，真气急运九大周天，内力汹涌滂湃，\n"+HIR"刹时间数股炽热刚猛的剑气自指中射出！！无数迅雷疾风相互冲撞激之际，\n"+HIW"竟然汇集成一束凌厉无匹的剑柱，宛如一条白色巨蟒,闪电般疾射向$n！！！\n"NOR,
	
	ap =  me->query_skill("force");
	ap += me->query_skill("finger");
	ap += me->query_str()*10;
	ap += random(ap/2);
	dp =  target->query_skill("force");
	dp += target->query_skill("parry");
	dp += target->query_dex()*10;
	dp += random(dp/2);
        ap += random(1+(int)me->query("jiali")/2);
        if (ap > dp || !living(target))
        {
                me->start_busy(2);
                if (! target->is_busy())
                target->start_busy(2 + random(2)); 
                
                damage = damage_power(me, "finger");
               
                damage = damage*3 + random(damage);
                damage += me->query("jiali")*2;
                damage += me->query("jianu")*(10+random(20));
                
                target->receive_damage("qi", damage,me);
                target->receive_wound("qi", damage/2,me);
                target->receive_damage("jing", damage,me);
                target->receive_wound("jing", damage/2,me);
                me->add("neili", -1000 );
                
                if( damage < 20 ) msg += HIY"结果$n受到$N的剑气击中，闷哼一声。\n"NOR;
                else if( damage < 40 ) msg += HIY"结果$n被$N的剑气击中，「嘿」地一声退了两步。\n"NOR;
                else if( damage < 80 ) msg += 
RED"结果$n被$N的剑气击中，胸口有如受到一记重锤，连退了五六步！\n"NOR;
                else msg += 
HIR"结果$n被$N的剑气击中，口中[哇]的吐出一口鲜血，身子如稻草人一般向后飞出丈许！！\n"NOR;

        } else 
 
 
        {
                me->start_busy(3);
                msg += CYN"可是$p看破了$P的招式，身子微微一闪已经避开了$P的『六脉归宗』！\n"NOR;
        }
        message_vision(msg, me, target);

        return 1;
}


