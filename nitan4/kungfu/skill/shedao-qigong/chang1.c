// ���ɷ�

#include <ansi.h>

int perform(object me)
{
	int skill;
	string msg;

	if (! me->is_fighting())
		return notify_fail("���ɷ�ֻ����ս����ʹ�á�\n");

	if ((int)me->query_skill("shedao-qigong", 1) < 60)
		return notify_fail("����ߵ��湦������죬����ʹ�ó��ɷ���\n");

	if ((int)me->query("neili") < 300)
		return notify_fail("���Ѿ����þ�ƣ���ߣ����������ˡ�\n");

	if ((int)me->query_temp("chang") == 30)
		return notify_fail("���Ѿ�����̫���ˣ������ٳ��ˡ�\n");

	skill = me->query_skill("force");

	me->add("neili", -200);

	message_combatd(HIR "ֻ��$N" HIR "���������дʣ����"
                        "֮���书�����\n" NOR, me);

	me->add_temp("apply/attack", 10);
	me->add_temp("apply/dodge", 10);
	me->add_temp("apply/force", 10);
	me->add_temp("apply/defense", 10);
	me->add_temp("chang", 1);

	return 1;
}