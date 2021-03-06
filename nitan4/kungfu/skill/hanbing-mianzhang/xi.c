// This program is a part of NITAN MudLIB
// xi.c 吸血青蝠
 
#include <ansi.h>
 
inherit F_SSERVER;
 
int perform(object me)
{
        string msg;
        object weapon, target;
        int skill, ap, dp, neili_wound, qi_wound;

        if (userp(me) && ! me->query("can_perform/hanbing-mianzhang/xi"))
                return notify_fail("你还没有领悟到这个绝招精华，无法施展「吸血青蝠」。\n");
                
        me->clean_up_enemy();
        target = me->select_opponent();

        skill = me->query_skill("hanbing-mianzhang", 1);

        if (! (me->is_fighting(target)))
                return notify_fail("「吸血青蝠」只能对战斗中的对手使用。\n");
 
        if (objectp(weapon = me->query_temp("weapon")))
                return notify_fail("你使用了武器。\n");

        if (skill < 60)
                return notify_fail("你的「寒冰绵掌」等级不够, 不能使用「吸血青蝠」！\n");

        if (me->query_skill("dodge", 1) < 200)
                return notify_fail("你的轻功基础还没有打好，无法运用「吸血青蝠」！\n");

 
        msg = HIR "$N" HIR "突然如同蝙蝠一样，倏的欺近$n"
              HIR "的身前，张嘴便向$n" HIR "的咽喉咬去。\n" NOR;
        message_combatd(msg, me, target);
 
        ap = attack_power(me, "strike");
        dp = defense_power(target, "dodge");
             
        if (ap / 2 + random(ap) > dp)
        {
                me->add("neili", -100);

                msg = HIG "$n" HIG "只觉得咽喉一阵剧痛，原来被$P" HIG
                      "要了个正中，只见$N" HIG "死死咬住狂吸$n" HIG "的鲜血！\n"NOR;
                neili_wound = damage_power(me, "strike") * 2;
                if (neili_wound > target->query("neili"))
                        neili_wound = target->query("neili");

                qi_wound = damage_power(me, "strike");
                if (qi_wound > target->query("qi"))
                        qi_wound = target->query("qi");

                target->add("neili", -neili_wound, me);
                      target->receive_damage("qi", qi_wound + 100, me);
                target->receive_wound("qi", qi_wound + 50, me);
                if( !target->is_busy() )
                target->start_busy(2);
                me->start_busy(1 + random(2));
        } else
        {
                msg = CYN "只见$n" CYN "不慌不忙，轻轻一闪，躲过了$N"
                      CYN "的利齿！\n"NOR;
                me->add("neili",-100);
                me->start_busy(4);
        }
        message_combatd(msg, me, target);

        return 1;
}

