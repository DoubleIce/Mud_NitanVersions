// This program is a part of NITAN MudLIB

#include <combat.h>
#include <ansi.h>

inherit F_SSERVER;

void remove_effect(object me, object target, int lvl1, int lvl2);
void check(object me, object target, int lvl1, int lvl2);

int perform(object me, object target)
{
        string msg;
        int lvl1, lvl2, amount;

        if (userp(me) && ! me->query("can_perform/jinyan-gong/yanwu"))
                return notify_fail("你还没有受过高人指点，无法施展「鹰飞雁舞」。\n");
                
        if( !target ) target = offensive_target(me);

        if( !target
        ||      !target->is_character()
        ||      !me->is_fighting(target) )
                return notify_fail("「鹰飞雁舞」轻功绝技只能对战斗中的对手使用。\n");

        if( me->query_temp("jyg-yanwu") )
                return notify_fail("你正在运用「鹰飞雁舞」轻功绝技！\n");

        /*
        if( me->query_skill_mapped("force") != "xiantian-gong")
                return notify_fail("你所用的内功与「鹰飞雁舞」轻功绝技运气方式相悖！\n");
        */

        if( me->query_skill_mapped("dodge") != "jinyan-gong")
                return notify_fail("你所用的身法与「鹰飞雁舞」招式不同，无法使用！\n");
                
        if( me->query_skill("dodge") < 134 )
                return notify_fail("你的身法修为不够，还无法施展「鹰飞雁舞」轻功绝技！\n");
                
        if( me->query_skill("force") < 59 )
                return notify_fail("你的内功修为火候未到，无法施展「鹰飞雁舞」轻功绝技！\n");

        if( me->query("neili") < 600 )
                return notify_fail("你的内力不够，劲力不足以施展「鹰飞雁舞」轻功绝技！\n");
        
        msg = HIC "$N清啸一声，身法陡然加快。$N的身影时如鹰击长空、时如群雁飞舞，令人眼花撩乱，煞是好看。\n\n" NOR;

        lvl1 = (int)me->query_skill("dodge");
        lvl2 = (int)me->query_skill("force");

        me->add_temp("apply/dex", lvl1 / 15);
        me->add_temp("apply/defense", lvl1 / 20);
        
        me->add("neili", -(lvl1+lvl2) / 3);

        me->start_call_out( (: call_other, __FILE__, "remove_effect", me, target, lvl1, lvl2:), (lvl1+lvl2)/15);
        message_combatd(msg, me);
        call_out("check", 1, me, target, lvl1, lvl2);
        me->set_temp("jyg-yanwu",1);
        return 1;
}

void remove_effect(object me, object target, int lvl1, int lvl2)
{
        if (!me || !me->query_temp("jyg-yanwu")) return;
        if( me->is_fighting())
                message_combatd(HIY "\n$N深吸一口气，收回「鹰飞雁舞」轻功绝技，$n顿时感到压力减轻了不少。\n" NOR, me, target);
        else message_vision(HIY "\n$N身形渐停，深吸一口气，收回了「鹰飞雁舞」轻功绝技。\n" NOR, me, target);
        me->delete_temp("jyg-yanwu",1);
        me->add_temp("apply/dex", -lvl1 / 15);
        me->add_temp("apply/defense", -lvl1 / 20);
}

void check(object me, object target, int lvl1, int lvl2)
{
        if (!me) return;
        else if( !me->is_fighting()){   
                remove_effect(me, target, lvl1, lvl2);
                return;
            } /*
        }else if( me->query_skill_mapped("dodge") != "jinyangong"){
                message_vision(HIY "\n$N的轻功已经不再是金雁功，「鹰飞雁舞」轻功绝技顿时消失。\n" NOR, me, target);        
                remove_effect(me, target, lvl1, lvl2);
                return;
        }
            */
        call_out("check", 1, me, target, lvl1, lvl2);
}



