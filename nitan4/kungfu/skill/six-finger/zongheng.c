#include <ansi.h>

inherit F_SSERVER;

int perform(object me, object target)
{
        string msg;
        int ap, dp;

        if (! target) target = offensive_target(me);

        if (! target || ! me->is_fighting(target))
                return notify_fail("���ݺ����¡�ֻ�ܶ�ս���еĶ���ʹ�á�\n");

        if (target->is_busy())
                return notify_fail(target->name() + "Ŀǰ���Թ˲�Ͼ���ŵ������ɣ�\n");
                
        if ((int)me->query_skill("six-finger", 1) < 120)
                return notify_fail("��������񽣻�򲻹�������ʹ�á��ݺ����¡���\n");

        if (me->query("neili") < 100)
                return notify_fail("��������������޷�ʩչ���ݺ����¡���\n");

        if (me->query_temp("weapon"))
                return notify_fail("�������ֲ���ʩչ���ݺ����¡���\n");

        if (me->query_skill_mapped("finger") != "six-finger")
                return notify_fail("��û�м��������񽣣��޷�ʩչ���ݺ����¡���\n");

        msg = HIW "ֻ��$N" HIW "һ����Ц��ʮָ�׵��������籼�������޾������ƽ�����Ȼ����$n" HIW "��\n" NOR;

        ap = attack_power(me, "finger");
        dp = defense_power(target, "force");
        if (ap / 2 + random(ap) > dp)             
        {
                msg += HIR "���$p" HIR "�����ݺύ���Ľ����Ƶ���æ���ң�Ӧ�Ӳ�Ͼ��\n" NOR;
                target->start_busy(random(4) + 3);
        } else
        {
                msg += CYN "����$p" CYN "�������ţ������ڹ���$P"
                       CYN "�Ľ����������⡣\n" NOR;
                me->start_busy(2);
        }
        message_combatd(msg, me, target);

        return 1;
}
