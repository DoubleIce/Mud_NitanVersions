// jue.c ���ɾ�
 
#include <ansi.h>
#include <combat.h>
 
inherit F_SSERVER;
 
int perform(object me, object target)
{
	string msg;
	int ap, dp;
        int damage;

        if (! target)
        {
        	me->clean_up_enemy();
        	target = me->select_opponent();
        }

	if (! target || ! me->is_fighting(target))
		return notify_fail("���ɾ�ֻ�ܶ�ս���еĶ���ʹ�á�\n");
 
	if (me->query_skill("bluesea-force", 1) < 120)
		return notify_fail("����Ϻ�������������죬����ʹ�þ��ɾ���\n");

        if (me->query("neili") < 200)
                return notify_fail("�����������������ʹ�þ��ɾ���\n");
 
       if (! living(target))
              return notify_fail("�Է����Ѿ������ˣ��ò�����ô�����ɣ�\n");

	msg = HIC "$N" HIC "������Ц��һ�ƻӳ����仯��������Ӱ����ס��$n"
              HIC "���е���·��\n" NOR;
 
        ap = attack_power(me, "force") + me->query("con") * 20;
        dp = defense_power(target, "parry") + target->query("dex") * 20;

        me->start_busy(2);
        me->add("neili", -50);
        if (ap / 2 + random(ap) < dp)
        {
		msg += HIG "Ȼ��$n" HIG "������$N" HIG
                       "�����ƣ����Ų�æ�Ķ������һ����\n" NOR;
        } else
	{
		me->add("neili",-75);
                damage = damage_power(me, "force");
                msg += COMBAT_D->do_damage(me, target, REMOTE_ATTACK, damage, 100,
                                           HIR "$n" HIR "������Ų������ȴ����ž����"
                                           "һ����$P" HIR "���ʵʵ�Ĵ�������ǰ����"
		                           "ʱ��Ѫ��ֹ��\n" NOR);
	}

	message_combatd(msg, me, target);
	return 1;
}