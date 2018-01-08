// Written by Lonely@IsMUD.net
// 所向无滞 转世技能
// wuzhi.c

#include <ansi.h>
inherit F_CLEAN_UP;

void remove_effect(object me, int skill);

int exert(object me, object target)
{
        int skill;
        
        if( me->query("family/family_name") != "古墓派" )
                return notify_fail("你不是古墓弟子，无法使用所向无滞。\n");

        if( !me->query("reborn/times") )        
                return notify_fail("你尚未转世重生，无法使用所向无滞！\n");
                
        if( (skill = me->query_skill("yunv-xinfa", 1)) < 1000 )
                return notify_fail("你的玉女心法还不够精熟，无法使用所向无滞！\n");
                        
        if( (int)me->query_temp("wuzhi") )
                return notify_fail("你已经在运起所向无滞了。\n");

        if( (int)me->query("jingli") < 2000 )
                return notify_fail("你的真气不够。\n");

        if( (int)me->query("neili") < 5000 )
                return notify_fail("你的内力不够。\n");

        me->add("neili", -1000);
        me->receive_damage("qi", 0);
        
        skill += me->query_skill("martial-cognize", 1);
        skill /= 300;
        
        message_combatd(HIY "只见$N" HIY "心静如水，内息再无停滞，心中武学如流水般挥洒开来。\n" NOR, me);
        
        me->add_temp("apply/ap_power", skill);
        me->add_temp("apply/add_xuruo", skill);
        me->add_temp("apply/add_busy", skill/2);
        me->add_temp("apply/double_damage", skill);
        me->set_temp("niepan", 1);

        me->start_call_out((: call_other, __FILE__, "remove_effect", me, skill :), skill);
        
        if( me->is_fighting() ) me->start_busy(2);

        return 1;
}

void remove_effect(object me, int skill)
{
        if( me->query_temp("niepan") ) {
                me->add_temp("apply/ap_power", -skill);
                me->add_temp("apply/add_xuruo", -skill);
                me->add_temp("apply/add_busy", -skill/2);
                me->add_temp("apply/double_damage", -skill);
                me->delete_temp("wuzhi");
                tell_object(me, "你的玉女心法运行完毕，将内力收回丹田。\n");
        }
}

