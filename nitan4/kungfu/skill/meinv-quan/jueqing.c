// wuqing.c ��Ůȭ-��Ů����
// by liu 24/07/2001
// Xuanyuan 5/9/2001�޸�

#include <ansi.h>

inherit F_SSERVER;

int perform(object me, object target)
{
	object ob;
	string msg;
	int damage,jiali,married,ap,dp;

	jiali = (int)me->query("jiali");

        if( !target ) target = offensive_target(me);

        if( !target || !target->is_character() || !me->is_fighting(target) )
                return notify_fail("��Ů����ֻ�ܶ�ս���еĶ���ʹ�á�\n");

        if( objectp(me->query_temp("weapon")) )
                return notify_fail("������ȷ������еı�����\n");

	if( me->query("gender") != "Ů��")
		return notify_fail("��Ů����ֻ��Ů�Բ��ܹ�ʹ�á�\n");

        if( (int)me->query_skill("meinv-quan", 1) < 400 )
                return notify_fail("�����Ůȭ���𲻹�������ʹ����Ů���顣\n");

        if( (int)me->query_skill("force", 1) < 120 )
                return notify_fail("����ڹ���δ��죬��������Ů���顣\n");

        if( (int)me->query("neili", 1) < 600 )
                return notify_fail("����������̫��������ʹ����Ů���顣\n");

        if( (int)me->query("jingli", 1) < 200 )
                return notify_fail("�����ھ���̫��������ʹ����Ů���顣\n");

	msg = HIB "\n\n$N�����߶�������ȭ���ݺ����飡\n"NOR;
        msg += HIY "\n$N����֧�ã���������ӳ�����̾һ�������ּ���֮�⣬������ʹ��ɱ�С�\n\n"NOR;

        ap = atoi(count_div(me->query("combat_exp"), 100));
        dp = atoi(count_div(target->query("combat_exp"), 100));
 	if (mapp(target->query("family")) && target->query("family/family_name") == "ȫ���")
		ap += ap/3;
        if( ap/2 + random( ap ) > dp || !living(target) )
        {
                damage = me->query_skill("force") + me->query_skill("unarmed") + me->query("jiali");
		damage += random(damage/2);

		//�жϽ������ͷ�������Ϊ�Ĵ���
		if (!mapp(me->query("couple"))) married = 1;
		else married = me->query("couple/married");
		if (mapp(me->query("sex"))) married += me->query("sex/times");
		damage -= (damage/5) * (married - 1);
		if (damage < 10) damage = 10;

		me->add("neili", -damage/2 );
		target->receive_damage("qi", damage,  me);
		target->receive_wound("qi", random(damage*2/3), me);
		target->start_busy(0);

		if ( damage < 1000) {
			msg += HIR"ֻ�����һ����$n��һȭ����С������Ѫ��ӿ��ڶ�����\n"NOR;
		}else if ( damage < 1800) {
			msg += HIR"ֻ���顢��������$n���۷��ࡢ���۷��ϣ���Ѫֱ����\n"NOR;
		}else if ( damage < 2600) {
			msg += HIR"ֻ���顢�顢�������죬$nͷ�����ز�������ͬʱ�����ػ��У���Ѫ���硣\n"NOR;
		}else {
			msg += HIR"ֻ���顢�顢�顢��������ﲻ����$nֱ����ù������ѷ��˳�ȥ��\n"NOR;
		}
		msg += NOR;
		me->start_busy(2+random(2));
  }
  else {
	 msg += HIG"$n���һ�֣�����Ծ�𣬱��ܵķ�Ӧ��$n�ӹ��˽١�\n\n"NOR;
	 me->add("neili", -100-(int)me->query("jiali"));
	 me->start_busy(2 + random(2));
	 message_vision(msg+"\n", me, target);
	 return 1;
  }

  message_vision(msg+"\n", me, target);
  COMBAT_D->report_status(target);
  return 1;
}