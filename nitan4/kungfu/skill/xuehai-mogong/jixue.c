// jixue.c 血海魔功祭血大法

#include <ansi.h>

inherit F_SSERVER;

void remove_effect(object me, int amount);

int exert(object me, object target)
{
        object weapon;  
        string msg;
        int skill;

        if ((int)me->query_temp("jixue"))
                return notify_fail(HIG"你已经运起祭血大法了。\n");

        if (! me->is_fighting())
                return notify_fail("「祭血大法」只能在战斗中使用。\n");

        if ((int)me->query("neili") < 200)
                return notify_fail("你的真气不够！\n");

        if ((int)me->query_skill("force") < 150)
                return notify_fail("你的血海魔功的修为不够，不能使用祭血大法！\n");
        msg = HIR "$N" HIR "使出血海魔功「祭血大法」，刹时间脸色变得"
              "血红，"HIR "$N" HIR "忽地咬破舌尖，喷出一口鲜血！\n" NOR;

        skill = (int)me->query_skill("xuehai-mogong", 1);

        if (me->query("qi") > me->query("max_qi") * 6 / 10)
        {       
                me->add_temp("apply/damage", skill*20);
                me->add_temp("apply/unarmed_damage", skill*20);
                me->set_temp("jixue", 1);
                me->start_call_out((: call_other, __FILE__, "remove_effect",
                                   me, skill :), skill);
                me->add("neili", -150);
                me->receive_damage("qi", me->query("max_qi") / 2);
        } else
                msg = HIR "$N" HIR "发现自己气力不济，没能提起祭血大法。\n" NOR;

        message_combatd(msg, me);
        return 1;
}

void remove_effect(object me, int amount)
{
        if ((int)me->query_temp("jixue"))
        {
                me->add_temp("apply/damage", -amount*20);
                me->add_temp("apply/unarmed_damage", -amount*20);
                me->delete_temp("jixue");
                tell_object(me, "你的祭血大法运行完毕，将内力收回丹田。\n");
        }
}

