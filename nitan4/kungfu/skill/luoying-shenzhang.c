inherit SKILL;
//by dream

mapping *action = ({
([      "action" : "$N������ָ����һ�գ�һʽ���ط����������ָ��Ȼ����$n�崦��Ѩ",
        "force"  : 80,
        "attack" : 14,
        "dodge"  : 7,
        "parry"  : 8,
        "damage" : 5,
        "lvl"    : 0,
        "damage_type" : "����",
        "skill_name"  : "�ط����"
]),
([      "action" : "$N��Ȼһ������ת���������䣬һʽ�����Ƿɻ���������$n��ͷ��",
        "force"  : 91,
        "attack" : 17,
        "dodge"  : 10,
        "parry"  : 13,
        "damage" : 9,
        "lvl"    : 20,
        "damage_type" : "����",
        "skill_name"  : "���Ƿɻ�"
]),
([      "action" : "$NͻȻԾ��˫�������������罣��һʽ���꼱��񡹣�����$n��ȫ��",
        "force"  : 108,
        "attack" : 22,
        "dodge"  : 17,
        "parry"  : 15,
        "damage" : 12,
        "lvl"    : 40,
        "damage_type" : "����",
        "skill_name"  : "�꼱���"
]),
([      "action" : "$NͻȻ������ˣ�һʽ�������׷ɡ���ƽ�����˫����$n��������",
        "force"  : 180,
        "attack" : 33,
        "dodge"  : 13,
        "parry"  : 16,
        "damage" : 28,
        "lvl"    : 60,
        "damage_type" : "����",
        "skill_name"  : "�����׷�"
]),
([      "action" : "$NͻȻ����Ծ�����Ʒ�����һʽ������׷�¡���������ǰ��$n��$l��ȥ",
        "force"  : 210,
        "attack" : 38,
        "dodge"  : 30,
        "parry"  : 25,
        "damage" : 33,
        "lvl"    : 80,
        "damage_type" : "����",
        "skill_name"  : "����׷��"
]),
([      "action" : "$Nʹһʽ���׺羭�졹��˫���������Ȧ������һ������$n��$l�ȥ",
        "force"  : 310,
        "attack" : 72,
        "dodge"  : 41,
        "parry"  : 55,
        "damage" : 68,
        "lvl"    : 100,
        "damage_type" : "����",
        "skill_name"  : "�׺羭��"
]),
([      "action" : "$Nһʽ����Ӣ���졹��˫������ǰ��ת���ƻ����裬����ǵ�ֱָ��$n",
        "force"  : 378,
        "attack" : 84,
        "dodge"  : 41,
        "parry"  : 65,
        "damage" : 103,
        "lvl"    : 120,
        "damage_type" : "����",
        "skill_name"  : "��Ӣ����"
]),
//��������
([      "action" : "[1;32m$Nһʽ�������项��˫��������������ǰ�ڶ�����ʱһ�����������ٳ���$n[2;37;0m",
        "force"  : 400,
        "attack" : 200,
        "dodge"  : 200,
        "parry"  : 200,
        "damage" : 250,
        "lvl"    : 300,
        "damage_type" : "����",
        "skill_name"  : "[1;32m������[2;37;0m"
]),
([      "action" : "[1;37m$N����Ӣ��������������ɣ�һ�С�����ն������Ȼ��շ��𣬵�ͷ��$nնȥ[2;37;0m",
        "force"  : 500,
        "attack" : 300,
        "dodge"  : 300,
        "parry"  : 300,
        "damage" : 350,
        "lvl"    : 350,
        "damage_type" : "����",
        "skill_name"  : "[1;37m����ն[2;37;0m"
]),
([      "action" : "[1;36m$N����Ӣ�������뷵豹��澳�磬����ȫ��������һ�С������̡����纣�˰��
                                                                                               
������$nӿȥ����ʱ���ɷ�Χ��ɳʯ�������ۼ�$n���޴�����[2;37;0m",
        "force"  : 850,
        "attack" : 500,
        "dodge"  : 500,
        "parry"  : 500,
        "damage" : 750,
        "lvl"    : 400,
        "damage_type" : "����",
        "skill_name"  : "[1;36m������[2;37;0m"
])
});

int valid_enable(string usage)
{
        return usage == "strike" || usage == "parry";
}

int valid_combine(string combo)
{
        return combo == "xuanfeng-tui";
}

int valid_learn(object me)
{
        if (me->query_temp("weapon") || me->query_temp("secondary_weapon"))
                return notify_fail("����Ӣ���Ʊ�����֡�\n");

        if ((int)me->query_skill("force") < 200)
                return notify_fail("��Ļ����ڹ���򲻹����޷�ѧ��Ӣ���ơ�\n");

        if ((int)me->query("max_neili") < 2000)
                return notify_fail("�������̫�����޷�����Ӣ���ơ�\n");

        if ((int)me->query_skill("strike", 1) < (int)me->query_skill("luoying-shenzhang", 1))
                return notify_fail("��Ļ����Ʒ�ˮƽ���ޣ��޷������������Ӣ���ơ�\n");

        /*
        if (me->query("character") == "���ռ�թ")
                return notify_fail("ѧϰ��Ӣ������Ҫ������ػ���û�д˵��ػ����޷�����ġ�\n");
        */

        if (me->query("str") < 22)
                return notify_fail("������������㣬�޷�������Ӣ���ơ�\n");

        if ((int)me->query_skill("strike", 1) < 200)
                return notify_fail("��Ļ����Ʒ�������죬�޷�������Ӣ���ơ�\n");

        if ((int)me->query_skill("strike", 1) < 200)
                return notify_fail("��Ļ����Ʒ�������죬�޷�������Ӣ���ơ�\n");

        return 1;
}

string query_skill_name(int level)
{
        int i;
        for (i = sizeof(action)-1; i >= 0; i--)
                if (level >= action[i]["lvl"])
                        return action[i]["skill_name"];
}

mapping query_action(object me, object weapon)
{
        int i, level;
        level = (int)me->query_skill("luoying-shenzhang", 1);
        for (i = sizeof(action); i > 0; i--)
                if (level > action[i-1]["lvl"])
                        return action[NewRandom(i, 20, level/5)];
}

int practice_skill(object me)
{
        if ((int)me->query("qi") < 300)
                return notify_fail("�������̫���ˡ�\n");

        if ((int)me->query("neili") < 100)
                return notify_fail("���������������Ӣ���ơ�\n");

        me->receive_damage("qi", 45);
        me->add("neili", -40);
        return 1;
}

string perform_action_file(string action)
{
        return __DIR__"luoying-shenzhang/" + action;
}

