// This program is a part of NITAN MudLIB

#include <ansi.h>
#include <combat.h>

#define JU "��" HIR "�۽���" NOR "��"

inherit F_SSERVER;

int perform(object me, object target)
{
        object weapon;
        int damage, ap, dp;
        string msg;

        if (userp(me) && ! me->query("can_perform/tianyu-qijian/ju"))
                return notify_fail("�㻹���˽�������е��˹����ţ��޷�ʩչ" JU "��\n");

        if (! target) target = offensive_target(me);

        if (! target || ! me->is_fighting(target))
                return notify_fail(JU "ֻ�ܶ�ս���еĶ���ʹ�á�\n");

        if (! objectp(weapon = me->query_temp("weapon")) ||
            (string)weapon->query("skill_type") != "sword")
                return notify_fail("��ʹ�õ��������ԣ�����ʩչ" JU "��\n");

        if (me->query_skill("tianyu-qijian", 1) < 130) 
                return notify_fail("��������潣������죬����ʩչ" JU "��\n");

        if (me->query_skill("force", 1) < 180)
                return notify_fail("����ڹ�����㣬����ʩչ" JU "��\n");

        if (me->query("neili") < 200) 
                return notify_fail("�����ڵ��������㣬����ʩչ" JU "��\n");
                        
        if (! living(target))
                return notify_fail("�Է����Ѿ������ˣ��ò�����ô�����ɣ�\n");

        ap = attack_power(me, "sword");
        dp = defense_power(target, "force");
             
        msg = HIR "$N" HIR "��������һ�������е�" + weapon->name() +
              HIR "����һ���ʺ磬�⻪ѣĿ��������$n" HIR "��\n" NOR;

        if (ap / 2 + random(ap) > dp)
        {
                damage = damage_power(me, "sword");

                me->add("neili", -100);
                msg += COMBAT_D->do_damage(me, target, WEAPON_ATTACK, damage, 50,
                                           HIR "ֻ��$N" HIR "������Ϊһ�ߣ�����$n"
                                           HIR "��$p" HIR "ֻ��һ���������Ķ�����"
                                           "��ͷһ����Ѫ���������\n" NOR);
                me->start_busy(1);
        } else 
        {
                msg += CYN "����$p" CYN "�͵���ǰһԾ,������$P"
                       CYN "�Ĺ�����Χ��\n"NOR;
                me->add("neili", -80);
                me->start_busy(3);
        }
        message_combatd(msg, me, target);

        return 1;
}

