// This program is a part of NITAN MudLIB
// wuchang.c 无常五化

#include <ansi.h>

inherit F_SSERVER;
 
int perform(object me, object target)
{
        object weapon;
        string msg;
        int i;

        //if (userp(me) && ! me->query("can_perform/wuchang-zhang/wuchang"))
        //        return notify_fail("你还没有受过高人指点，无法施展「无常五化」。\n");
 
        if (! target)
        {
                me->clean_up_enemy();
                target = me->select_opponent();
        }

        if (! target || ! me->is_fighting(target))
                return notify_fail("「无常五化」只能对战斗中的对手使用。\n");
 
        if (! objectp(weapon = me->query_temp("weapon")) ||
            (string)weapon->query("skill_type") != "staff")
                return notify_fail("施展「无常五化」时必须拿着一把剑！\n");

        if ((int)me->query("neili") < 100)
                return notify_fail("你的真气不够，无法施展「无常五化」！\n");

        if ((int)me->query_skill("force") < 200)
                return notify_fail("你的内功火候不够，难以施展「无常五化」！\n");

        if ((int)me->query_skill("wuchang-zhang", 1) < 150)
                return notify_fail("你的无常杖法还不到家，无法使用「无常五化」！\n");

        if (me->query_skill_mapped("staff") != "wuchang-zhang")
                return notify_fail("你没有激发无常杖法，不能使用「无常五化」！\n");

       if (! living(target))
              return notify_fail("对方都已经这样了，用不着这么费力吧？\n");

        msg = HIY "$N" HIY "将手中的" + weapon->name() +
             HIY "一荡，化作无数杖影扫向$n" HIY "！\n" NOR;
        message_combatd(msg, me, target);

        me->add("neili", -100);

        for (i = 0; i < 5; i++)
        {
                if (! me->is_fighting(target))
                        break;
                if (random(3) == 1 && ! target->is_busy())
                        target->start_busy(2);
                COMBAT_D->do_attack(me, target, weapon, 0);
        }

        me->start_busy(2);
        return 1;
}

