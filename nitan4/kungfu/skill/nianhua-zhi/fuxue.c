// This program is a part of NITAN MudLIB
// fuxue.c �黨ָ ���黨��Ѩ��

#include <ansi.h>

inherit F_SSERVER;

int perform(object me, object target)
{
        string msg;
        int ap, dp;

        //if (userp(me) && ! me->query("can_perform/nianhua-zhi/fuxue"))
        //        return notify_fail("�㻹û���ܹ�����ָ�㣬�޷�ʩչ���黨��Ѩ����\n");
                
        if (! target) target = offensive_target(me);

        if (! target || ! me->is_fighting(target))
                return notify_fail("�黨��Ѩֻ�ܶ�ս���еĶ���ʹ�á�\n");

        if ((int)me->query_skill("force") < 150)
                return notify_fail("���ڹ���򲻹�������ʹ���黨��Ѩ��\n");

        if ((int)me->query_skill("finger") < 150)
                return notify_fail("���ָ����Ϊ������Ŀǰ������ʹ���黨��Ѩ������\n");

        if ((int)me->query("neili") < 200)
                return notify_fail("��������������������ʹ���黨��Ѩ��\n");

        if (target->is_busy())
                return notify_fail(target->name() + "Ŀǰ���Թ˲�Ͼ���ŵ������ɣ�\n");

        if (me->query_skill_mapped("finger") != "nianhua-zhi") 
                return notify_fail("��û�м����黨ָ���޷�ʹ���黨��Ѩ��\n");

       if (! living(target))
              return notify_fail("�Է����Ѿ������ˣ��ò�����ô�����ɣ�\n");

        msg = HIY "$N" HIY "ʹ���黨ָ�������黨��Ѩ������ס��$n"
              HIY "��ȫ��ָ���������Ĺ���$p" HIY "��ҪѨ��\n" NOR;

        ap = attack_power(me, "finger");
        dp = defense_power(target, "dodge");

        if (ap / 2 + random(ap) > dp)
        {
                msg +=  HIG "���$p" HIG "��$P" HIG "���˸����ֲ�����\n" NOR;
                if (! target->is_busy())        
                        target->start_busy(random(2) + 3);
                me->add("neili", -100);
                me->start_busy(1 + random(2));
        }
        else
        {
                msg += CYN "����$p" CYN "������$P"
                       CYN "����ʽ����æԾ�����ܿ���$P"
                       CYN "�Ĺ�����\n" NOR;
                me->add("neili", -30);
                me->start_busy(3);
        }
        message_combatd(msg, me, target);

        return 1;
}

