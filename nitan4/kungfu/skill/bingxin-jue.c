// by dream
// bingxin-jue.c ���ľ�

#include <ansi.h>

inherit FORCE;

int valid_force(string force) { return 1; }       

int query_neili_improve(object me)  
{
        int lvl; 
        lvl = (int)me->query_skill("bingxin-jue", 1); 
        return lvl * lvl * 22 * 15 / 100 / 200; 
}

int valid_enable(string usage) { return usage == "force"; }

int valid_learn(object me)
{
        int lvl = (int)me->query_skill("bingxin-jue", 1);


        if (me->query("gender") == "����" && lvl > 20)
                return notify_fail("���޸����ԣ������������޷�������ľ��ľ���֮����\n");

        if ((int)me->query_skill("force") < 200)
                return notify_fail("����ڹ����̫ǳ��\n");

        return ::valid_learn(me);
}

int practice_skill(object me)
{
        return notify_fail("���ľ�ֻ����ѧ(learn)�������������ȡ�\n");
}

string exert_function_file(string func)
{
        return __DIR__"bingxin-jue/" + func;
}

