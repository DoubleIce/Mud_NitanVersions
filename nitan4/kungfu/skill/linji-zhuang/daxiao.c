// Code of JHSH
// daxiao.c

#include <ansi.h>

int exert(object me, object target)
{
	int level = me->query_skill("linji-zhuang", 1);
	int amount;

	if (level < 150) return notify_fail("����ټ�ʮ��ׯ��Ϊ��������\n");

	if( (int)me->query("max_neili") < 5*level ) 
		return notify_fail("�������������ǿ��\n");

	if( (int)me->query("neili") < 4*level ) 
		return notify_fail("�������������\n");

	if( (int)me->query("eff_qi") < (int)me->query("max_qi"))
		return notify_fail("��������Ѫ���ˣ�ֻ���޷����ھ���ƽ�⣡\n");
	
	if( (int)me->query("eff_jing") < (int)me->query("max_jing"))
		return notify_fail("�����ھ������ˣ�ֻ���޷����ھ���ƽ�⣡\n");

	if ( me->query_temp("linji/daxiao") )
		return notify_fail("���Ѿ��˹����ھ�����С�ˡ�\n");

	me->set_temp("linji/daxiao", 1);
	write( HIY "����Ϣ�������������д�С��ׯ��ֻ��һ��ů�������ţ����ػ�������ȫ����������һ�ܣ����뵤��������\n" NOR);
        message_combatd(
		HIY + "ֻ��" + me->name() + "��Ϣ������ͷ��Ʈ��һ���ư�������̬����ƣ����\n" NOR,
                me);

	amount = me->query("max_jing") - me->query("max_qi");
	amount /= 2;

	me->add("max_qi", amount);
	me->add("max_jing", -amount);
	me->set("eff_qi", me->query("max_qi"));
	me->set("eff_jing", me->query("max_jing"));
	if (me->query("qi") > me->query("max_qi"))
		me->set("qi",me->query("max_qi"));
	if (me->query("jing") > me->query("max_jing"))
		me->set("jing",me->query("max_jing"));

	me->add("neili", -4*level);

	me->start_call_out( (: call_other, __FILE__, "remove_effect", me, amount :), 1800);

	return 1;
}

void remove_effect(object me, int level)
{
	me->add("max_qi", -level);
	me->add("max_jing", level);
	me->set("eff_qi", me->query("max_qi"));
	me->set("eff_jing", me->query("max_jing"));
	if (me->query("qi") > me->query("max_qi"))
		me->set("qi",me->query("max_qi"));
	if (me->query("jing") > me->query("max_jing"))
		me->set("jing",me->query("max_jing"));
	me->delete_temp("linji/daxiao");

	tell_object(me, HIG"���д�С��ׯ�Ѿã��ָֻ���ԭ�о�����\n"NOR);
}