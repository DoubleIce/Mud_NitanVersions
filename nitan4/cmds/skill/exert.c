// exert.c

#include <skill.h>
#include <ansi.h>

inherit F_CLEAN_UP;

int main(object me, string arg)
{
	string force;
	int result;
        function f; 
        int r;
	
	seteuid(getuid());

	if (me->is_busy())
		return notify_fail("( ����һ��������û����ɣ�����ʩ���ڹ���)\n");

	if (! arg)
		return notify_fail("��Ҫ���ڹ���ʲô��\n");

        if (me->query_condition("no_exert"))
                return notify_fail(HIR "��ֻ������Ϣһ�����ң������޷�������Ϣ��\n" NOR);

        f = me->query_temp("override/exert", 1); 
        if (functionp(f)) 
                r = (*f)(me, arg); 
        if (r) return r;

	if (stringp(force = me->query_skill_mapped("force")))
        {
        	notify_fail("���޷�˳������ת��Ϣ��\n");
        	if (SKILL_D(force)->do_effect(me))
                	return 0;

		notify_fail("����ѧ���ڹ���û�����ֹ��ܡ�\n");
		if (SKILL_D(force)->exert_function(me, arg))
                {
			if (random(120) < (int)me->query_skill("force"))
				me->improve_skill(force, 1, 1);
			return 1;
		} else if (SKILL_D("force")->exert_function(me, arg))
                {
			if (random(120) < (int)me->query_skill("force", 1))
				me->improve_skill("force", 1, 1);
			return 1;
		}
		return 0;
	}

	return notify_fail("�������� enable ָ��ѡ����Ҫʹ�õ��ڹ���\n");
}

int help (object me)
{
        write(@HELP
ָ���ʽ��exert|yun <��������> [<ʩ�ö���>]

����������һЩ���칦�ܣ������Ҫָ��<��������>��<ʩ�ö���>����п��ޡ�
����ʹ��ĳһ���ڹ������칦��֮ǰ����������� enable ָ����ָ����Ҫʹ��
���ڹ���

��ο� help force �ɵ�֪һЩ�󲿷��ڹ����еĹ��ܣ����������õ��ڹ�����
��û�иù��ܣ���һ�Ի�ο�����˵����֪��

ע�������ı��Լ����ڹ�����ԭ�����������������ֱ��ת����ȥ������
    �ӣ���ʼ��

HELP );
        return 1;
}
