// This program is a part of NITAN MudLIB
// mian 绵绵不绝


#include <ansi.h>
#include <combat.h>

inherit F_SSERVER;
int perform(object me, object target)
{
        string msg,x;
        int i,j,k,y;

        //if (userp(me) && ! me->query("can_perform/paiyun-shou/mian")) 
        //        return notify_fail("你还没有受过高人指点，无法施展「绵绵不绝」。\n"); 
                        
        if( !target ) target = offensive_target(me);
        if( !target || !me->is_fighting(target) )
                return notify_fail("「绵绵不绝」只能在战斗中对对手使用。\n");
                
        if( objectp(me->query_temp("weapon")) )
                return notify_fail("使用「绵绵不绝」时必须空手！\n");
                
        if( (int)me->query_skill("paiyun-shou", 1) < 120 )
                return notify_fail("你的排云推手不够娴熟，不会使用「绵绵不绝」。\n");
                
        if( (int)me->query("max_neili") < 1100 )
                return notify_fail("你现在内力修为不够，不能使用「绵绵不绝」。\n");
                
        if( (int)me->query("neili") < 500 )
                return notify_fail("你现在内力太弱，不能使用「绵绵不绝」。\n");
                
        if( me->query_skill_prepared("hand") != "paiyun-shou"
        ||  me->query_skill_mapped("hand") != "paiyun-shou")
                return notify_fail("你必须全面运用排云推手，才能使用「绵绵不绝」。\n");

                
        i = (me->query_skill("paiyun-shou", 1)/5);
        if( target->is_busy() ) i*=2;
        if( (int)me->query_skill("paiyun-shou", 1) > 400 )
        {
                y = 10;
        } else 
        if( (int)me->query_skill("paiyun-shou", 1) > 180 )
        {
                y = 8;      
        }
        else 
        {
                y = 6;
        }
        msg = HIY "$N忽然身随掌起，双掌圈动，似虚而实，似柔而刚。一掌拍出，第二掌接踵而至，一连"+chinese_number(y)+"掌，其意如排云滚滚。\n" NOR;
        message_combatd(msg, me, target);
        me->add_temp("apply/attack", i);
        
        for(k = 0; k < y; k++)
        {
                COMBAT_D->do_attack(me, target, me->query_temp("weapon"), TYPE_QUICK);
        }
        me->add_temp("apply/attack", -i);
        me->add("neili", -400);
        me->start_busy(2);
        return 1;
}

