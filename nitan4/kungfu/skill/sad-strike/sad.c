// This program is a part of NITAN MudLIB
// sad.c 黯然消魂

#include <ansi.h>

inherit F_SSERVER;
 
int perform(object me, object target)
{
        string msg;
        int ap, dp;
        int count;
        int i;

        if (userp(me) && ! me->query("can_perform/sad-strike/xiao"))
                return notify_fail("你未得高人指点，不知该如何施展「黯然销魂」。\n");
                 
        if (! target)
        {
                me->clean_up_enemy();
                target = me->select_opponent();
        }

        if (! target || ! me->is_fighting(target))
                return notify_fail("「黯然销魂」只能在战斗中对对手使用。\n");
 
        if (me->query_temp("weapon") || me->query_temp("secondary_weapon"))
                return notify_fail("「黯然销魂」只能空手使用。\n");
                
        if ((int)me->query("neili") < 500)
                return notify_fail("你的真气不够！\n");

        if ((int)me->query_skill("sad-strike", 1) < 180)
                return notify_fail("你的黯然销魂掌火候不够，无法施展「黯然销魂」。\n");

        if ((int)me->query_skill("force") < 300)
                return notify_fail("你的内功修为不够，无法施展「黯然销魂」。\n");

        if (me->query_skill_mapped("unarmed") != "sad-strike")
                return notify_fail("你现在没有准备使用黯然销魂掌，无法施展「黯然销魂」。\n");

       if (! living(target))
              return notify_fail("对方都已经这样了，用不着这么费力吧？\n");

        msg = HIM "$N" HIM "一声长叹，心如止水，黯然神伤，于不经意中随"
              "手使出了" HIR "『黯然销魂』" HIM "！\n" NOR;

        ap = attack_power(me, "unarmed") +
             me->query_skill("force");

        dp = defense_power(target, "parry") +
             target->query_skill("force");
             
        if (ap / 2 + random(ap) > dp)
        {
                count = ap / 10;
                msg += HIY "$n" HIY "见$P" HIY "这一招变化莫测，奇幻无"
                       "方，不由大吃一惊，慌乱中破绽迭出。\n" NOR;
        } else
        {
                msg += HIC "$n" HIC "不敢小觑$P" HIC
                       "的来招，腾挪躲闪，小心招架。\n" NOR;
                count = 0;
        }

        message_combatd(msg, me, target);
        me->add_temp("apply/attack", count);

        me->add("neili", -200);
        for (i = 0; i < 6; i++)
        {
                if (! me->is_fighting(target))
                        break;
                if (random(3) == 0 && ! target->is_busy())
                        target->start_busy(1);

                COMBAT_D->do_attack(me, target);
        }

        me->start_busy(2 + random(4));
        me->add_temp("apply/attack", -count);

        return 1;
}
