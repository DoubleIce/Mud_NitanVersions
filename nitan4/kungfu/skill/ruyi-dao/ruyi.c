// This program is a part of NITAN MudLIB

#include <ansi.h>
#include <combat.h>

#define RUYI "「" HIC "如意六刀" NOR "」"

inherit F_SSERVER;
 
int perform(object me, object target)
{
        object weapon;
        string msg;
        int i, skill;
 
        if (userp(me) && ! me->query("can_perform/ruyi-dao/ruyi"))
                return notify_fail("你还没有受过高人指点，无法施展" RUYI "。\n");

        if (! target)
        {
                me->clean_up_enemy();
                target = me->select_opponent();
        }

        if (! target || ! me->is_fighting(target))
                return notify_fail(RUYI "只能对战斗中的对手使用。\n");
 
        if (!objectp(weapon = me->query_temp("weapon")) ||
            (string)weapon->query("skill_type") != "blade")
                return notify_fail("你的武器不对，难以施展" RUYI "。\n");

        if ((int)me->query("neili") < 250)
                return notify_fail("你的真气不够，难以施展" RUYI "。\n");

        if ((int)me->query_skill("force") < 100)
                return notify_fail("你的内功火候不够，难以施展" RUYI "。\n");

        if (me->query_skill("ruyi-dao", 1) < 100)
                return notify_fail("你的如意刀法还不到家，难以施展" RUYI "。\n");

        if (me->query_skill_mapped("blade") != "ruyi-dao")
                return notify_fail("你没有激发如意刀法，难以施展" RUYI "。\n");

        if (! living(target))
                return notify_fail("对方都已经这样了，用不着这么费力吧？\n");

        msg = HIC "$N" HIC "使出逍遥绝技「如意六刀」，身法忽然奇快无比，变幻莫测！\n" NOR;
        message_combatd(msg, me);
        me->add("neili", -120);
        skill = me->query_skill("ruyi-dao", 1);
        me->add_temp("apply/attack", skill / 5);
        for (i = 0; i < 6; i++)
        {
                if (! me->is_fighting(target))
                        break;
                COMBAT_D->do_attack(me, target, weapon, 0);
        }
        me->add_temp("apply/attack", -skill / 5);
        me->start_busy(2 + random(4));

        return 1;
}

