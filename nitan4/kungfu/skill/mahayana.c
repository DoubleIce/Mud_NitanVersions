//mahayana.c  ������͹�
#include <ansi.h>
inherit SKILL;

string type() { return "knowledge"; }

int valid_learn(object me)
{
    if ((int)me->query("shen") < 0 )
       return notify_fail("���а��̫�أ��޷�����������͹���\n");

    return 1;
}

void skill_improved(object me)
{
        if ((int)me->query_skill("mahayana", 1) == 120 && ! me->query("em/dex") && me->query("gender") != "����")
        {
                me->add("dex", 1);
                me->set("em/dex", 1);
                tell_object(me, HIM "\n��Ĵ�����͹�ѧ�����ɣ�������������\n" NOR);
        }
}
