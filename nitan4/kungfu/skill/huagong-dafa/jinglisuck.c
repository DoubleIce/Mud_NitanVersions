// Code of JHSH
// jinglisuck.c

#include <ansi.h>

inherit F_DBASE;
inherit F_SSERVER;

int exert(object me, object target)
{
        int sp, dp, jl;

        if( !target ) target = offensive_target(me);

        if( !objectp(target) || target == me)
                return notify_fail("你要吸取谁的精力？\n");

        if (environment(me)->query("no_fight"))
                return notify_fail("这里不能战斗，你不可以使用化功大法吸人的精力。\n");

        if ( me->query_temp("sucked") )
                return notify_fail("你刚刚吸取过精力！\n");

        if( objectp(me->query_temp("weapon")) )
                return notify_fail("必须空手才能够吸取别人的精力！\n");

        if( !me->is_fighting() || !target->is_fighting() || !living(target) )
                return notify_fail("你必须在战斗中才能吸取对方的精力！\n");

        if( (int)me->query_skill("huagong-dafa",1) < 90 )
                return notify_fail("你的化功大法功力不够，不能吸取对方的内力！\n");

        if( (int)me->query("neili") < 300 )
                return notify_fail("你的内力不够，不能使用化功大法。\n");

        if( (int)me->query("jingli") < 100 )
                return notify_fail("你的精力不够，不能使用化功大法。\n");

        if( (int)me->query("jingli") >= (int)me->query("max_jingli") * 5/2 )
                return notify_fail("你吸取的精力充塞全身，无法再吸取精力！\n");

        if( (int)target->query("max_jingli") <= 0 )
                return notify_fail( target->name() +
                        "没有任何精力！\n");

        if( (int)target->query("jingli") < (int)target->query("max_jingli") / 10 )
                return notify_fail( target->name() + "已经精力涣散，你已经无法从他体内吸取任何精力了！\n");

	
        message_vision(HIR "$N朝$n微微一笑，突然翻掌变爪，扣向$n的手腕！\n\n" NOR, me, target );

        if( !target->is_killing(me) ) target->kill_ob(me);

        sp = me->query_skill("force") + me->query_skill("dodge") + me->query("kar")*50;
        dp = target->query_skill("force") + target->query_skill("dodge") + target->query("kar")*50;
        sp *= atoi(count_div(me->query("combat_exp"), 1000));
        dp *= atoi(count_div(target->query("combat_exp"), 1000));

        me->set_temp("sucked", 1);              

        if( random(sp+dp) > dp )
        {
                tell_object(target, HIR "你腕内会宗穴被" + me->name() + "突然扣住，动弹不得，只觉精力如洪水般自会宗穴奔腾而出！\n" NOR);
                tell_object(me, HIG "你觉得" + target->name() + "的精力自手掌源源不绝地流了进来。\n" NOR);

		jl = (1+random(3)) * (int)me->query_skill("huagong-dafa", 1)/2;
		if ((int)target->query("jingli") > jl)
		{		
	                target->add("jingli", -1 * jl );
	                me->add("jingli", jl);
		}else{
	                me->add("jingli", jl/2);
	                target->add("jingli", -jl/2 );
	                }
                if( count_ge(target->query("combat_exp"), count_div(me->query("combat_exp"), 2)) ) {
                        me->add("potential", 1);
                        me->add("combat_exp", 1);
                        if (count_gt(me->query("potential"), me->query_potential_limit()))
                        me->set("potential", me->query_potential_limit());
                }

                me->start_busy(1+random(3));
                target->start_busy(1+random(3));
                me->add("neili", -(int)me->query_skill("huagong-dafa", 1)/6);
                me->add("jingli", -5);

                call_out("del_sucked", 2, me);
        }
        else
        {       
                message_vision(HIY "可是$p看破了$P的企图，没让$P扣住手腕。\n" NOR, me, target);
                me->add("jingli", -20);
                me->start_busy(2+random(2));
                call_out("del_sucked", 5, me);
        }

        return 1;
}

void del_sucked(object me)
{
        if ( me->query_temp("sucked"))
        me->delete_temp("sucked");
}

