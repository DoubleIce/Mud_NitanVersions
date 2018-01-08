inherit SKILL;

string type() { return "knowledge"; }

int valid_learn(object me)
{
        int gift, mat;

        gift = 35;
        mat = 300;

        if (me->query("family/family_name") == "�һ���")
        {
                gift = 30;
                mat = 200;
        }

        if (! me->query("family/family_name") ||
            me->query("family/family_name") != "�һ���")
                return notify_fail("�㲻���һ������ӣ���������������Եİ��\n");
        
        if ((int)me->query("int") < gift)
                return notify_fail("����������Բ��㣬��������������Եİ��\n");

        if ((int)me->query_skill("mathematics", 1) < mat)
                return notify_fail("�������֪ʶ̫��޷�����������Եİ��\n");

        if ((int)me->query_skill("mathematics", 1) < (int)me->query_skill("count", 1))
                return notify_fail("�������֪ʶ���ޣ��޷�������µ��������ԡ�\n");

        if (me->query_skill("zuoyou-hubo", 1) && !me->query("special_skill/capture"))
                return notify_fail("����ܵ����һ�������֮��Ӱ�죬��������������Եİ��\n");

        return 1;
}
