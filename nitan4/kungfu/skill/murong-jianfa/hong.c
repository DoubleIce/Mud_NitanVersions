// This program is a part of NITAN MudLIB

#include <ansi.h>
#include <combat.h>

#define NING "��" HIM "�׺����" NOR "��"

inherit F_SSERVER;
 
int perform(object me, object target)
{
        object weapon;
        string msg;
        int ap, dp;
        int damage;
 
        if (! target) target = offensive_target(me);

        if (userp(me) && ! me->query("can_perform/murong-jianfa/hong"))
                return notify_fail("�㻹û���ܹ�����ָ�㣬�޷�ʩչ" NING "��\n");

        if (! target || ! me->is_fighting(target))
                return notify_fail(NING "ֻ����ս���жԶ���ʹ�á�\n");

        if (! objectp(weapon = me->query_temp("weapon")) ||
              (string)weapon->query("skill_type") != "sword")
                return notify_fail("��ʹ�õ��������ԣ�����ʩչ" NING "��\n");

        if (me->query_skill("dodge", 1) < 100)
                return notify_fail("��Ļ����Ṧ����Ϊ����������ʩչ" NING "��\n");

        if (me->query_skill("force", 1) < 100)
                return notify_fail("��Ļ����ڹ�����Ϊ����������ʩչ" NING "��\n");

        if (me->query_skill("murong-jianfa", 1) < 100)
                return notify_fail("���Ľ�ݽ�����Ϊ����������ʩչ" NING "��\n");

        if (me->query_skill_mapped("sword") != "murong-jianfa")
                return notify_fail("��û�м���Ľ�ݽ���������ʩչ" NING "��\n");

        if (me->query("neili") < 250)
                return notify_fail("��������������������ʩչ" NING "��\n");

        if (! living(target))
                return notify_fail("�Է����Ѿ������ˣ��ò�����ô�����ɣ�\n");

        msg = HIW "\n$N" HIW "���һ�����������ʹ�����С�" HIM "�׺����" HIW "����������������"
              + weapon->name() + HIW "�ϣ���ʱ�������䣬������磬ǿ��Ľ���׷��$n��\n" NOR;

        ap = attack_power(me, "sword");
        dp = defense_power(target, "parry");

        if (ap / 2 + random(ap) > dp)
        {
                damage = damage_power(me, "sword");
                
                me->add("neili", - 150);
                me->start_busy(1);
                msg += COMBAT_D->do_damage(me, target, WEAPON_ATTACK, damage, 55,
                                           HIR "$n" HIR "���ϲ���������������ȴ�Ѿ��н���\n" NOR);
        } else
        {
                me->add("neili", -100);
                me->start_busy(2);
                msg += CYN "����$n" CYN "�����мܣ��������л��⡣\n"NOR;
        }

        message_sort(msg, me, target);

        return 1;
}

