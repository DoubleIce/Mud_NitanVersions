// Written by Lonely@IsMUD.net
// 佛光普照 转世技能
// buddha.c

#include <ansi.h>
inherit F_CLEAN_UP;

void remove_effect(object me);

int exert(object me, object target)
{
        int skill;
        
        if( me->query("family/family_name") != "少林派" )
                return notify_fail("你不是少林弟子，无法使用佛光普照。\n");

        if( !me->query("reborn/times") )        
                return notify_fail("你尚未转世重生，无法使用佛光普照！\n");
                
        if( target != me )
                return notify_fail("你只能用易筋经来激发佛光普照。\n");

        if( (skill = me->query_skill("yijinjing", 1)) < 1000 )
                return notify_fail("你的易筋经神功没有学成，无法使用佛光普照！\n");

        if( me->query_skill("jingang-buhuaiti", 1) < 1000 )
                return notify_fail("你的金刚不坏体神功修为不够，无法使用佛光普照！\n");

        if( me->query_skill("buddhism", 1) < 1000 )
                return notify_fail("你对禅宗心法的参悟还不够，无法使用佛光普照！\n");
        
        if( me->query_skill_mapped("parry") != "jingang-buhuaiti" )
                return notify_fail("你必须激发金刚不坏体，才能使用佛光普照！\n");

        if( (int)me->query_temp("buddha") )
                return notify_fail("你已经在运起佛光普照了。\n");

        if( (int)me->query("jingli") < 2000 )
                return notify_fail("你的真气不够。\n");

        if( (int)me->query("neili") < 5000 )
                return notify_fail("你的内力不够。\n");

        me->add("neili", -1000);
        me->receive_damage("qi", 0);

        message_combatd(HIY "只听$N" HIY "高呼佛号，运起佛光普照，霎那间全身竟犹如镀金一般，发出灿灿金光。\n" NOR, me);

        me->set_temp("apply/avoid_busy_effect", 1);
        me->set_temp("apply/avoid_xuruo_effect", 1);
        me->set_temp("apply/avoid_damage_effect", 1);
        me->set_temp("buddha", 1);

        me->start_call_out((: call_other, __FILE__, "remove_effect", me :), skill/10);
        
        if( me->is_fighting() ) me->start_busy(2);

        return 1;
}

void remove_effect(object me)
{
        if( me->query_temp("buddha") ) {
                me->delete_temp("apply/avoid_busy_effect");
                me->delete_temp("apply/avoid_xuruo_effect");
                me->delete_temp("apply/avoid_damage_effect");
                me->delete_temp("buddha");
                tell_object(me, "你运行完毕，将内力收回丹田，佛光消失。\n");
        }
}

