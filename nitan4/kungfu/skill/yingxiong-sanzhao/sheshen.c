// sheshen.c 舍身技
/*              msg += HIC "$n不料$N用此招数，手忙脚乱，狼狈万状的躲闪开去，但已吓得手足冰凉，好一阵动弹不得。\n" NOR;
*/

#include <ansi.h>

inherit F_SSERVER;


int perform(object me, object target)
{
        mapping skill_status;
        string msg, *sname;
        object weapon;
        int exp, shen, mine, count;

        if( !target ) target = offensive_target(me);

        if( !target
        ||      !target->is_character()
        ||      !me->is_fighting(target) )
                return notify_fail("舍身只能对战斗中的对手使用。\n");

        if( me->is_ghost() || me->query("eff_qi") <0 )
                return notify_fail("你已经死了。\n");


        if( me->is_busy() )
                return notify_fail("你现在忙着呢，使不出这一招。\n");


//        if( !me->query("yinliting_teach") )
//                 return notify_fail("你未得教主传授，不会使用舍身。\n");

        if( (int)me->query_skill("strike") < 250 )
                return notify_fail("你的英雄三招极不够娴熟，不会使用舍身。\n");
//        if( me->query("neili") >= 100 || me->query("qi") >= 200)
//                                               return notify_fail("你未到山穷水尽之地，不需用此狠招！\n")
        if( (int)me->query_skill("shenlong-xinfa", 1) < 250 && (int)me->query_skill("busi-shenlong", 1) < 250 )
                return notify_fail("你的内功修为不够，不会使用舍身。\n");

        if( me->query_skill_mapped("force") != "shenlong-xinfa" && me->query_skill_mapped("force") != "busi-shenlong" )
                                         return notify_fail("你所用的内功于英雄三招气路相悖！\n");

                  if( count_lt(me->query("combat_exp"), 500000) )
                                         return notify_fail("你实战经验不足，不会使用舍身。\n");

        if (target->query("shen") > 10000)
                shen = - (int)me->query("shen")/50;
        else shen = (int)me->query("shen")/50;

        exp = atoi(count_div(me->query("combat_exp"), 100));

        msg = HIW"$N一声悲啸，空门大开，全身撞向$n"+HIW"，已经是拼命的打法！！！\n"NOR;

//        mine = random(me->query("combat_exp") -me->query("shen"));
        mine = random(atoi(count_div(count_sub(me->query("combat_exp"), me->query("shen")), 100)));
        
//        if( mine > (int)target->query("combat_exp")/3*2 )
        if( count_gt(count_mul(mine, 3), count_div(target->query("combat_exp"), 50)) )
        {
                msg += HIR"$n"+HIR"猝不及防之下，被$N扑个正着，只觉浑身灼热无比，却又浑身动弹不得，\n忍不住了发出一声声凄厉的惨叫！！！$n面目变的狰狞可怕，垂死前的挣扎终于停止了。\n两人都耗尽所有的气力，只留下惊心动魄的悲惨一幕！！！\n" NOR;
                message_vision(msg, me, target);
                me->add("max_neili", -(30+random(30)) );
                me->add("combat_exp", -exp);
                me->add("shen", shen);
                me->receive_wound("qi", me->query("max_qi")+200);
                target->receive_wound("qi", target->query("max_qi")+200);
                me->start_busy(3 + random(3));
                target->start_busy(3 + random(3));
                me->set_temp("die_reason","与"+target->name(1)+"同归于尽");
                target->set_temp("die_reason","与"+me->name(1)+"同归于尽");
                me->die();
                target->die();
                return 1;

        } 
        else
        {
                msg += HIC "$n" HIC "不料$N" HIC "用此招数，手忙脚乱，狼狈万状的躲闪开去，但已吓得手足冰凉，好一阵动弹不得。\n"NOR;
                message_vision(msg, me, target);
                me->receive_wound("qi", me->query("max_qi")+200);
                me->start_busy(3);
                me->die();
                target->start_busy(3 + random(3));
                return 1;

        }

        return 1;
}

