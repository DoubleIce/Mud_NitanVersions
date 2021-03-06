// This program is a part of NITAN MudLIB
// wang.c 天罗地网 「天罗地网」

#include <ansi.h>
#include <combat.h>

inherit F_SSERVER;

int perform(object me, object target)
{
        string msg;
        object weapon;
        int skill, ap, dp;
        
        skill = me->query_skill("tianluo-diwang", 1);
        
        /*
        if( userp(me) && ! me->query("can_perform/tianluo-diwang/wang") )
                return notify_fail("你未得高人指点，不知该如何施展「天罗地网」。\n");
        */
              
        if( !target ) target = offensive_target(me);
        if( !target
        ||      !target->is_character()
        ||      !me->is_fighting(target) )
                return notify_fail("「天罗地网」只能在战斗中使用。\n");

        if((int)me->query_str() < 25)
                return notify_fail("你臂力不够,不能使用这一绝技!\n");

        if((int)me->query_skill("yunv-xinfa",1) < 100)
                return notify_fail("你玉女心经的功力不够不能使用天罗地网!\n");

        if((int)me->query_skill("strike") < 120)
                return notify_fail("你的掌法修为不够,目前还不能使用天罗地网绝技!\n");

        if((int)me->query("neili") < 300)
                return notify_fail("你内力现在不够, 不能使用天罗地网! \n");

        if( target->is_busy() )
                return notify_fail(target->name() + "目前正自顾不暇，放胆攻击吧ⅵ\n");

        if( target->query_temp("luowang") )
                return notify_fail("对手已在你的天罗地网势之中！\n");

        msg = HIM "\n但见$N双臂飞舞，出手挡击回臂反扑发掌奇快，但一招一式清清楚楚自成" +
              "段落，两只手掌宛似化成了千手千掌！\n" NOR;

        ap = attack_power(me, "strike");
        dp = defense_power(target, "dodge");
             
        if (ap / 2 + random(ap) > dp)
        {
                msg += CYN "\n$n心下大骇，飞滚翻扑，始终逃不出$N只掌所围作的圈子! \n" NOR;

                target->start_busy( 3 + skill / 100 );
                target->add_temp("apply/defense", -skill/8);
                target->set_temp("luowang",1);
                me->add("neili", -150);
                remove_call_out("checking");
                call_out("checking", 1, me, target,skill);
                if( userp(target)) call_out("remove_effect", skill/20, me, target, skill); 
                        else call_out("remove_effect", skill/30, me, target, skill);
        }
        else
        {
                msg += HIY "\n可是$p气定神弦，看破了$P的诱惑，纵身一跃，跳了开去。\n" NOR;
                me->start_busy(1+random(3));
                me->add("neili", -100);
                return 1;
        }
        message_combatd(msg, me, target);
        return 1;
}

void checking(object me, object target, int skill)
{
        if ( ! objectp(target) || ! objectp(me) ) return;
        if ( target->query_temp("luowang_finished"))
                target->delete_temp("luowang_finished");
        else {
        if( !living(me) || me->is_ghost() )
        {
                target->delete_temp("luowang");
                target->add_temp("apply/defense", skill/8);
                remove_call_out("remove_effect");
                message_combatd(HIG"慢慢的，$n已不似初见时那么诧异万分。\n\n"NOR,me,target);
                return ;
        }
        if( !me->is_fighting() )
        {
                target->delete_temp("luowang");
                target->add_temp("apply/defense", skill/8);
                remove_call_out("remove_effect");
                message_combatd(HIG"慢慢的，$n已不似初见时那么诧异万分。\n\n"NOR,me,target);
                return ;
        }

        if( me->query_skill_mapped("strike") != "tianluo-diwang"
         || me->query_skill_prepared("strike") != "tianluo-diwang" )
        {
                message_combatd(HIM"\n$N骤然变换招数，不能再继续用天罗地网牵制对手的攻击！\n"NOR, me);
                target->delete_temp("luowang");
                target->add_temp("apply/defense", skill/8);
                remove_call_out("remove_effect");
                message_combatd(HIG"慢慢的，$n已不似初见时那么诧异万分。\n\n"NOR,me,target);
                return ;
        }

        else call_out("checking", 1, me, target,skill);
                return;
        }
        return;
}

private int remove_effect(object me, object target, int skill)
{
        if (! objectp(target)) return 0;
        target->delete_temp("luowang");
        target->add_temp("apply/defense", skill/8);
        target->set_temp("luowang_finished",1);
        message_vision(HIG"慢慢的，$N已不似初见时那么诧异万分。\n\n"NOR, target);
        return 1;
}
