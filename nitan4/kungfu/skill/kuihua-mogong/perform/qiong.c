// qiong �����޾�

#include <ansi.h>
#include <combat.h>

inherit F_SSERVER; 

#define QIONG "��" HIR "�����޾�" NOR "��"
 
int perform(object me, object target)
{
	string msg;
        int ap, ap1, dp1, damage;
        mixed dp;
        object weapon;

	if (! target) target = offensive_target(me);

	if (! target || ! me->is_fighting(target))
	        return notify_fail(QIONG "ֻ����ս���жԶ���ʹ�á�\n");

	if (me->query_skill("kuihua-mogong", 1) < 250)
		return notify_fail("��Ŀ���ħ����������죬����ʹ��" QIONG "��\n");

        if ((int)me->query("max_neili") < 3800)
                return notify_fail("���������Ϊ���㣬����ʩչ" QIONG "��\n");

	if (me->query("neili") < 200)
		return notify_fail("��������������޷�ʩչ" QIONG "\n");

        if (weapon = me->query_temp("weapon"))
        {
                if (weapon->query("skill_type") != "sword" &&
                    weapon->query("skill_type") != "pin")
                        return notify_fail("�������õĲ��ǽ�����ôʩ"
                                           "չ" QIONG "��\n");
        } else
        {
                if (me->query_skill_prepared("finger") != "kuihua-mogong")
                        return notify_fail("�㲢û��׼��ʹ�ÿ�"
                                           "��ħ�������ʩչ" QIONG "��\n");
        }
        if (weapon && me->query_skill_mapped("sword") != "kuihua-mogong")
                return notify_fail("��û��׼��ʹ�ÿ���ħ��������ʩչ" QIONG "��\n");

        if (! weapon && me->query_skill_prepared("finger") != "kuihua-mogong")
                return notify_fail("��û��׼��ʹ�ÿ���ħ��������ʩչ" QIONG "��\n");

        if (! living(target))
               return notify_fail("�Է����Ѿ������ˣ��ò�����ô�����ɣ�\n");

        msg = HIR "\n$N" HIR "��Хһ������Ȼ������ǰ��һ�о�ֱϮ$n" HIR "Ҫ�����ٶ�֮�죬��"
              "�˼���δ��������δ�š�\n" NOR;

        ap = attack_power(me, "unarmed");
        dp = defense_power(target, "force");
        
        if (ap / 2 + random(ap) > dp)
        {
	        me->want_kill(target);
                ap = me->query_skill("kuihua-mogong", 1);
                dp = atoi(count_div(target->query("combat_exp"), 10000));
	        me->add("neili", -60);
	        me->start_busy(1 + random(2));

                if (dp >= 10000) // �԰�����������Ч��������Ȼ�ܵ��˺�
                {
                        if (weapon) damage = damage_power(me, "sword");
                        else damage = damage_power(me, "unarmed");
                        msg += COMBAT_D->do_damage(me, target, REMOTE_ATTACK, damage, 95 + random(5),
                                                HIR "��һ���ٶ�֮����ȫ������$n" HIR "������$n" HIR
                                                "��æ�����мܣ����Ǵ���֮�죬���޴Ӷ�����$n" HIR "���"
                                                "һ������Ȼ���С�\n" NOR);

                        message_sort(msg, me, target);
                        return 1;
                } else
                // if (random(ap) > dp)
                {
                        msg += HIR "��һ���ٶ�֮����ȫ������$n" HIR "�����󣬱�$N"
                               HIR "��һ�����û����˵���Ҫ��������������ʱ��ɢ��\n" NOR;
                        message_combatd(msg, me, target);
                        me->add("neili", -120);
                        target->receive_damage("qi", 1, me);  
                        target->die(me);
                        return 1;
                }

        } else
                msg += HIM "$n" HIM "���һ������æ�˺󣬾�Ȼ"
                                "���Ҷ㿪����һ�У�\n" NOR;
        
        me->start_busy(1 + random(2));                        
        message_combatd(msg, me, target);

	return 1;
}
