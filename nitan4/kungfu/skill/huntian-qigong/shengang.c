// This program is a part of NITAN MudLIB
// shengang.c 混天气功混天神罡

#include <ansi.h>
#include <combat.h>
#include <weapon.h>
#include <skill.h>
inherit F_SSERVER;

void remove_effect(object me, int amount);

int exert(object me, object target)
{
        object weapon;  
        string msg;
        int d_count, count, qi, maxqi, skill;
        
        weapon = me->query_temp("weapon"); 
        
        if (! me->query("can_exert/huntian-qigong/shengang"))
                return notify_fail(HIG "你还没有受到某人的指点，还不会使用这种功夫。\n" NOR);
                
        if (me->query_temp("shield")) 
                return notify_fail(HIG "你已经在运混元天罡了。\n" NOR);
                
        if ((int)me->query("neili") < 200)
                return notify_fail("你的内力还不够！\n");

        if ((int)me->query_skill("huntian-qigong", 1) < 150)
                return notify_fail("你的混天气功的修为不够，不能使用混元天罡! \n");
                
        msg = WHT "$N使出混天气功绝学「混元天罡」，一股白气自顶心泥丸发散而下，全身弥漫在白色薄雾中！\n" NOR;

        qi = me->query("qi");
        maxqi = me->query("max_qi");
        skill = (int) (me->query_skill("huntian-qigong", 1) / 6);
        count = me->query_str();
        d_count = (int)me->query_dex() / 2;

        if (qi > (maxqi * 0.4))
        {       
                message_combatd(msg, me, target);
                me->add_temp("apply/damage", skill*20);
                me->add_temp("apply/unarmed_damage", skill*20);
                me->add_temp("apply/attack", skill*2);
                me->add_temp("apply/defense",skill*2);
                me->add_temp("apply/dex", skill);
                me->set_temp("shield", 1);
                me->start_call_out( (: call_other, __FILE__, "remove_effect", me, skill * 2 :), skill);

                me->add("neili", -150);
        } else
        {
                msg = HIR "$N拼尽毕生功力想提起混元天罡，但自己受伤太重，没能成功!\n" NOR;
        }
        return 1;
}

void remove_effect(object me, int amount)
{
        if ((int)me->query_temp("shield")) 
        {
                message_combatd("白色的薄雾渐渐散去，$N的身形步法又变的清晰可见。\n", me);
                me->add_temp("apply/damage", - amount*10);
                me->add_temp("apply/unarmed_damage", - amount*10);
                me->add_temp("apply/attack", -amount);
                me->add_temp("apply/dex", -amount / 2);
                me->add_temp("apply/defense", -amount);

                me->delete_temp("shield");
                tell_object(me, HIY "你的混元天罡运行完毕，将内力收回丹田。\n" NOR);
        }
}

