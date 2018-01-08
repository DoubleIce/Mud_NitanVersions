// This program is a part of NITAN MudLIB

#include <ansi.h>
#include <combat.h>

#define DING "��" HIR "������" NOR "��"

inherit F_SSERVER;

int perform(object me, object target)
{
        object weapon;
        int damage, ap, dp;
        string msg;

        /*
        if (userp(me) && ! me->query("can_perform/quanzhen-jian/ding"))
                return notify_fail("��δ�ø���ָ�㣬��֪�����ʩչ" DING "��\n"); 
        */
        
        if (! target) target = offensive_target(me);

        if (! target || ! me->is_fighting(target))
                return notify_fail(DING "ֻ�ܶ�ս���еĶ���ʹ�á�\n");

        if (! objectp(weapon = me->query_temp("weapon")) ||
            (string)weapon->query("skill_type") != "sword")
                return notify_fail("����ʹ�õ��������ԣ�����ʩչ" DING "��\n");

        if ((int)me->query_skill("quanzhen-jian", 1) < 100)
                return notify_fail("��ȫ�潣��������죬����ʩչ" DING "��\n");

        if ((int)me->query_skill("force") < 150)
                return notify_fail("����ڹ���򲻹�������ʩչ" DING "��\n");

        if ((int)me->query("neili") < 150)
                return notify_fail("����������̫��������ʩչ" DING "��\n");

        if (me->query_skill_mapped("sword") != "quanzhen-jian")
                return notify_fail("��û�м���ȫ�潣��������ʩչ" DING "��\n");

        if (! living(target))
                return notify_fail("�Է����Ѿ������ˣ��ò�����ô�����ɣ�\n");

        msg = HIC "$N" HIC "�������Ҽ�����������������������һʽ��"
              HIR "������" NOR + HIC "��бб�̳���\n" NOR;

        me->start_busy(2);
        ap = attack_power(me, "sword");
        dp = defense_power(target, "dodge");

        if (ap / 2 + random(ap) > dp) 
        {
                damage = damage_power(me, "sword");

                me->add("neili", -100);
                msg += COMBAT_D->do_damage(me, target, WEAPON_ATTACK, damage, 50,
                                           HIR "$n" HIR "����$N" HIR "������ǧ��"
                                           "��һ��������֪����мܣ���ʱ�����ش�"
                                           "��\n" NOR);
        } else
        {
                msg += CYN "����$p" CYN "������$P"
                       CYN "����ͼ��бԾ�ܿ���\n" NOR;
                me->add("neili", -30);
        }
        message_combatd(msg, me, target);

        return 1;
}