// by Lonely

#include <ansi.h>
void remove_effect(object me,int count);

int exert(object me)
{
/*
        if ( !me->is_fighting())
                return notify_fail("你只能在战斗中使用「金刚不坏体神功」！\n");
*/

        if( (int)me->query_skill("yijinjing", 1) < 400 )
                return notify_fail("你的易筋经内功修为不够，无法使用「金刚不坏体神功」！\n");

        if (me->query_skill_mapped("force") != "yijinjing")
                return notify_fail("其它内功有「金刚不坏体神功」吗？\n");

        if( (int)me->query_con() < 40 )
                return notify_fail("你的根骨太低，根本无法使用「金刚不坏体神功」！\n");
 
        if( (int)me->query("neili") < 1000 )
                return notify_fail("你目前的内力太少了，无法使用「金刚不坏体神功」！\n");   
    
        if( (int)me->query("max_neili") < 3800 )
                return notify_fail("你的内力修为这么差，还想使用「金刚不坏体神功」？\n");   
        
        if( me->query_temp("jin"))
                return notify_fail("你正在运用着呢！\n");
                                                                                                
        if( me->query_temp("sl/jiuyang"))
                return notify_fail("你正在运用「少林九阳神功」！\n");
       
        message_combatd(HIY"\n$N突然深吸一口气，目露慈光，面带微笑，内力运转，竟使全身上下宝光流动，是「金刚不坏体神功」！\n\n" NOR, me);
        me->start_busy(1);

        me->set_temp("jin", 1);
        me->set_temp("nopoison", 1);
        me->add_temp("apply/armor", me->query_skill("yijinjing", 1)/2); 
        me->add("neili", -500);  
          
        call_out("remove_effect", 1, me, me->query_skill("yijinjing", 1)/2+20);
      
        return 1;
}

void remove_effect(object me, int count)
{
        if( !me) return;
        if (count < 0)
        {
                me->delete_temp("nopoison");
                me->delete_temp("jin");
                me->add_temp("apply/armor", - me->query_skill("yijinjing", 1) / 2);
                message_vision(HIR"\n$N双手合十，散去了凝聚于全身上下的「金刚不坏体神功」。\n"NOR, me);    
                return;
        }
        else {
                call_out("remove_effect", 1, me,count -1);
        }
}

int help(object me)
{
        write(HIY"\n易筋经之「金刚不坏体神功」："NOR"\n");
        write(@HELP
        金刚，坚利之意，历百劫千生，流转六道，而觉性不坏。即以金刚之坚，喻
        般若体；以金刚之利，喻般若用。金刚不坏体神功为少林第一大绝技，以易
        筋经为本，使神、体、气三者相融，循序渐进，持之以恒，便能抵御心魔，
        抗击外力。
        
        要求：  易筋经等级 200 以上；
                根骨 40 以上；
                最大内力 3800 以上；
                内力 1000 以上。
HELP
        );
        return 1;
}

