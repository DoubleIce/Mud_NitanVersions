// prepare.c

inherit F_CLEAN_UP;

mapping valid_types = 
([
	"finger":   "ָ��",
	"hand":     "�ַ�",
	"cuff":     "ȭ��",
	"claw":     "צ��",
	"strike":   "�Ʒ�",
	"unarmed":  "ȭ��",
]);

int main(object me, string arg)
{
	mapping smap, pmap;
	array skill;
	string basic1, basic2, arg1, arg2, arg3;
        string msg;
	int i, count;

	seteuid(getuid());

	smap = me->query_skill_map();

	if (! mapp(smap) || sizeof(smap) == 0)
		return notify_fail("������û��ʹ���κ���Ч���⼼�ܡ�\n");

	pmap = me->query_skill_prepare();
	if (! pmap) pmap = ([]);

	if (! arg)
	{
		if (! mapp(pmap) || sizeof(pmap) == 0)
			return notify_fail("������û������κ�����ȭ�����ܡ�\n");

		skill = keys(valid_types);
		msg = "��������Ŀǰ����е�����ȭ�����ܡ�\n";
		for (i = 0; i < sizeof(skill); i++)
                {
			if (! me->query_skill(skill[i]) ||
			    ! pmap[skill[i]]) continue;
			msg += valid_types[skill[i]] + " (" + skill[i] + ")" +
			       "   " + to_chinese(pmap[skill[i]]) + "\n";
		}
                write(msg);
		return 1;
	}

	if (arg == "?") 
	{
		msg = "�����ǿ���ʹ������ȭ�����ܵ����ࣺ\n";
		skill = sort_array(keys(valid_types), (: strcmp :));
		for(i = 0; i < sizeof(skill); i++)
			msg += sprintf("  %s (%s)\n", valid_types[skill[i]], skill[i]);
                write(msg);
		return 1;
	}

	if (arg == "none")
	{
		if (! mapp(pmap) || sizeof(pmap) == 0)
			return notify_fail("������û������κ�����ȭ�����ܡ�\n");

		skill = keys(pmap);
		for (i = 0; i < sizeof(skill); i++)
			me->prepare_skill(skill[i]);

		me->reset_action();
		write("ȡ��ȫ������׼����\n");
		return 1;
	}

	if (sizeof(pmap) >= 2)
		return notify_fail("�������Ѿ�������������⼼�ܡ�\n");

        basic1 = 0;
        basic2 = 0;
	if (sscanf(arg, "%s %s %s", arg1, arg2, arg3) >= 3)
		return notify_fail("ָ���ʽ��prepare|bei [<��������һ>|<�������ƶ�>]\n");

	if (sscanf(arg, "%s %s", arg1, arg2) == 2)
	{
		if (sizeof(pmap) == 1)
			return notify_fail("����׼����һ�ּ����ˡ�\n");
		else
		{
                        if (me->query_skill_mapped(arg1))
                        {
                                basic1 = arg1;
                                arg1 = me->query_skill_mapped(arg1);
                        }

                        if (me->query_skill_mapped(arg2))
                        {
                                basic2 = arg2;
                                arg2 = me->query_skill_mapped(arg2);
                        }

			if (! me->query_skill(arg1, 1) || ! me->query_skill(arg2, 1))
				return notify_fail("�����ٲ��������ּ�������֮һ��\n");

			if (! SKILL_D(arg1)->valid_combine(arg2))
				return notify_fail("������ȭ�����ܲ�����ϡ�\n");

			skill = keys(valid_types);
			for (i = 0; i < sizeof(skill); i++)
                        {
                                if (! basic1 && smap[skill[i]] == arg1) basic1 = skill[i];
				if (! basic2 && smap[skill[i]] == arg2) basic2 = skill[i];
			}

			if (! basic1 || ! basic2)
				return notify_fail("������ȭ����δ������Ŀǰ����׼����\n");

                        if (! valid_types[basic1])
                                return notify_fail(to_chinese(arg1) + "���ּ��ܲ���Ҫ׼����\n");

                        if (! valid_types[basic2])
                                return notify_fail(to_chinese(arg2) + "���ּ��ܲ���Ҫ׼����\n");

			me->prepare_skill(basic1, arg1);
			me->prepare_skill(basic2, arg2);

			me->reset_action();
			write("��ɼ���׼����\n");
			return 1;
		}		
	}

	if (sscanf(arg, "%s", arg1) == 1 && sizeof(pmap) <= 1)
	{
                if (me->query_skill_mapped(arg1))
                {
                        basic1 = arg1;
                        arg1 = me->query_skill_mapped(arg1);
                }

		if (! me->query_skill(arg1, 1))
			return notify_fail("�㲻�����ּ��ܡ�\n");

		skill = keys(pmap);

                if (sizeof(pmap) == 1 &&
                   ! SKILL_D(arg1)->valid_combine(pmap[skill[0]]))
                        return notify_fail("���ּ��ܲ���������м�����ϡ�\n");

		skill = keys(valid_types);
		for (i = 0; i < sizeof(skill); i++)
			if (! basic1 && smap[skill[i]] == arg1) basic1 = skill[i];

		if (! basic1)
			return notify_fail("���ּ�����δ������Ŀǰ����׼����\n");

                if (! valid_types[basic1])
                        return notify_fail(to_chinese(arg1) + "���ּ��ܲ���Ҫ׼����\n");

		me->prepare_skill(basic1, arg1);
		me->reset_action();
		write("��ɼ���׼����\n");
	
		return 1;
	}
	
	return 1;
}

int help(object me)
{
        write(@HELP
ָ���ʽ : prepare|bei [<ȭ����������>|<ȭ����������> | none]
           prepare|bei ?

���ָ������ָ����Ҫ�õ�ȭ�����ܣ� ��ָ��һ�����ϵ���Ӧ�������ơ�
������Ӳ��������ʾ���������༰��Ŀǰ��ʹ�õļ������� �������һ
�������г�������ʹ������ȭ�����ܵļ������ࡣ
 
HELP );
        return 1;
}
