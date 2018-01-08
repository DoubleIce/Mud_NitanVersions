#include <ansi.h>
#include <combat.h>

#define JING "��" HIR "����һ��" NOR "��"

inherit F_SSERVER;

int perform(object me, object target)
{
        object weapon;
        int damage;
        string msg;
        int ap, dp;

        if (userp(me) && ! me->query("can_perform/duanjia-jian/jing"))
                return notify_fail("�㻹û���ܹ�����ָ�㣬�޷�ʩչ" JING "��\n");

        if (! target)
        {
                me->clean_up_enemy();
                target = me->select_opponent();
        }

        if (! target || ! me->is_fighting(target))
                return notify_fail(JING "ֻ�ܶ�ս���еĶ���ʹ�á�\n");

        if (! objectp(weapon = me->query_temp("weapon")) ||
            (string)weapon->query("skill_type") != "sword")
                return notify_fail("��ʹ�õ��������ԣ�����ʩչ" JING "��\n");

        if ((int)me->query_skill("duanjia-jian", 1) < 80)
                return notify_fail("��Ķμҽ���������죬����ʩչ" JING "��\n");

        if (me->query_skill_mapped("sword") != "duanjia-jian")
                return notify_fail("������û�м����μҽ�������ʩչ" JING "��\n");

        if ((int)me->query_skill("force") < 80)
                return notify_fail("����ڹ���Ϊ����������ʩչ" JING "��\n");

        if ((int)me->query("neili") < 300)
                return notify_fail("�����ڵ���������������ʩչ" JING "��\n");

        if (! living(target))
                return notify_fail("�Է����Ѿ������ˣ��ò�����ô�����ɣ�\n");

        msg = HIR "$N" HIR "һԾ��������һ�������һ�������Ľ���������$n"
              HIR "��ȥ��\n"NOR;

        ap = attack_power(me, "sword");
        dp = defense_power(target, "force");

        if (ap / 2 + random(ap) > dp)
        {
                damage = damage_power(me, "sword");
                me->add("neili", -150);
                msg += COMBAT_D->do_damage(me, target, WEAPON_ATTACK, damage, 55,
                                           HIR "ֻ��$N" HIR "�˽���һ������$n"
                                           HIR "��$n" HIR "ֻ��һ���������Ķ�"
                                           "������ͷһ����Ѫ���������\n" NOR);
                me->start_busy(2);
        } else 
        {
                msg += CYN "����$p" CYN "�͵������һԾ��������$P"
                       CYN "�Ĺ�����Χ��\n"NOR;
                me->add("neili", -100);
                me->start_busy(3);
        }
        message_combatd(msg, me, target);

        return 1;
}
