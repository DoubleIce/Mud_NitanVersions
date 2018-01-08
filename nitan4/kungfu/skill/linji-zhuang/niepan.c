// Written by Lonely@IsMUD.net
// 凤凰涅磐 转世技能
// buddha.c

#include <ansi.h>
inherit F_CLEAN_UP;

void remove_effect(object me);

int exert(object me, object target)
{
        int skill;
        
        if( me->query("family/family_name") != "峨嵋派" )
                return notify_fail("你不是少林弟子，无法使用凤凰涅磐。\n");

        if( !me->query("reborn/times") )        
                return notify_fail("你尚未转世重生，无法使用凤凰涅磐！\n");
                
        if( skill = me->query_skill("linji-zhuang", 1) < 1000 )
                return notify_fail("你的临济十二庄修为还不够，无法使用凤凰涅磐！\n");

        if( (int)me->query_temp("niepan") )
                return notify_fail("你已经在运起凤凰涅磐了。\n");

        if( (int)me->query("jingli") < 2000 )
                return notify_fail("你的真气不够。\n");

        if( (int)me->query("neili") < 5000 )
                return notify_fail("你的内力不够。\n");

        if( target != me ) {
                if( !target->query_xuruo() )
                        return notify_fail(target->name() + "并没有处于虚弱状态。\n");
                
                me->add("neili", -1000);
                me->receive_damage("qi", 0);
                target->clear_xuruo();
                message_combatd(HIY "只见$N" HIY "屏息静气，双掌贴在"+target->name()+"背后，交错运行大小二庄，只见"+target->name()+"全身被紫芒笼罩。\n" NOR, me);
                tell_object(target, HIG"\n你感觉身体状态慢慢的复原了。。。\n\n" NOR); 
                tell_object(me, HIG"\n你替"+target->name()+"消除了虚弱状态。。。\n\n" NOR); 
                if( me->is_fighting() ) me->start_busy(3);
                return 1;
        }

        me->add("neili", -1000);
        me->receive_damage("qi", 0);

        message_combatd(HIY "$N" HIY "神色忽而欢叹、忽而忧心、转瞬间又化做不喜不悲之状，\n随著$N" HIY "张开眼神，一屡精光乍现及逝，$N"HIY"的气习却已全然不同。\n" NOR, me);

        me->set_temp("apply/avoid_busy_effect", 1);
        me->set_temp("apply/avoid_xuruo_effect", 1);
        me->add_temp("apply/reduce_damage", 30);
        me->set_temp("niepan", 1);

        me->start_call_out((: call_other, __FILE__, "remove_effect", me :), skill/10);
        
        if( me->is_fighting() ) me->start_busy(2);

        return 1;
}

void remove_effect(object me)
{
        if( me->query_temp("niepan") ) {
                me->delete_temp("apply/avoid_busy_effect");
                me->delete_temp("apply/avoid_xuruo_effect");
                me->add_temp("apply/reduce_damage", -30);
                me->delete_temp("niepan");
                tell_object(me, "你的临济庄运行完毕，将内力收回丹田。\n");
        }
}

