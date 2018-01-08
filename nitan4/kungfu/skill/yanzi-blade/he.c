// This program is a part of NITAN MudLIB

#include <ansi.h>
#include <combat.h>

#define XUE "��" HIW "˫���ϱ�" NOR "��"

inherit F_SSERVER;

int perform(object me, object target)
{
        string type, msg;
        object weapon1, weapon2;
        int i, count, damage;
        int ap, dp;

        if (userp(me) && ! me->query("can_perform/yanzi-blade/he"))
                return notify_fail("�㻹û���ܹ�����ָ�㣬�޷�ʩչ" XUE "��\n");

        if (! target)
        {
                me->clean_up_enemy();
                target = me->select_opponent();
        }

        if (! me->is_fighting(target))
                return notify_fail(XUE "ֻ�ܶ�ս���еĶ���ʹ�á�\n");
        
        weapon1 = me->query_temp("weapon"); 
        weapon2 = me->query_temp("handing"); 

        if (! objectp(weapon1) || ! objectp(weapon2))
                return notify_fail("��û��ͬʱװ��˫��������ʩչ" XUE "��\n");

        if (weapon2->query("consistence") <= 0)
                return notify_fail("���" + weapon2->name() + "�Ѿ�����"
                                   "�𻵣��޷�����ʹ���ˡ�\n");

        if (weapon1->query("skill_type") != weapon2->query("skill_type") ||
            weapon1->query("skill_type") != "blade")
                return notify_fail("����ʹ�õ��������ԣ�����ʩչ" XUE "��\n");

        type = weapon1->query("skill_type");

        if (me->query_skill(type, 1) < 250)
                return notify_fail("���" + to_chinese(type) + "̫�"
                                   "����ʩչ" XUE "��\n");

        if (me->query_skill_mapped(type) != "yanzi-blade")
                return notify_fail("��û�м�������˫�ɵ���������ʩչ" XUE "��\n");

        if (me->query_skill("yanzi-blade", 1) < 250)
                return notify_fail("�������˫�ɵ����ȼ�����������ʩչ" XUE "��\n");

        if (me->query("neili") < 500)
                return notify_fail("�����ڵ���������������ʩչ" XUE "��\n");

        if (! living(target))
                return notify_fail("�Է����Ѿ������ˣ��ò�����ô�����ɣ�\n");

        msg = HIW "$N" HIW "�ֳ����ѵ�������$n " HIW "����������һɲ�Ǽ䣬���ѵ��·��Ȼ�����һ�ѵ���\n"
              HIW "˫���ϱڣ�������������һ����������һǧ���������������Ϊ��ǧ�����������һ�����ٶȵ�ȻҲҪ����һ����\n"
              HIW "$N" HIW "˫���ϱڣ����ѵ������Ѻ϶�Ϊһ��ȴ��ƫƫ�·��Ǵ�������ͬ�ķ����������ġ�\n"
              HIW "�����ǿ���$n" HIW "���ұߣ�����$n" HIW "�������ܣ�������������$n" HIW "������������������\n" NOR;
        
        ap = attack_power(me, "blade");
        dp = defense_power(target, "parry");

        if (ap / 2 + random(ap * 2) > dp)
        {
                damage = damage_power(me, "blade") * 2;
                me->add("neili", -150);
                msg += COMBAT_D->do_damage(me, target, WEAPON_ATTACK, damage, 85,
                                           HIR "ֻ��$n" HIR "һ���ҽУ��ؿڸ�"
                                           "����һ���޴�Ŀ��ӣ���Ѫ��ӿ�����\n" NOR);
                me->start_busy(2);
                if (ap / 3 + random(ap / 2) > dp && ! target->is_busy())
                        target->start_busy(3);
        } else
        {
                msg += CYN "$p" CYN "���һ����Ҳ���мܣ��������"
                       "�������ߣ��ܿ���$P" CYN "��һ�С�\n" NOR;
                me->add("neili", -50);
                me->start_busy(3);
        }
        message_combatd(msg, me, target);

        return 1;
}

