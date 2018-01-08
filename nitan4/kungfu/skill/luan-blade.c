// This program is a part of NITAN MudLIB
// Luan-blade.c �ҵ����ﲮ�⣩

inherit SKILL;

string *action_msg = ({
        "$N����$w��һ����һ������׼$n��$l����һ��",
        "$N����$w��һ����һ�ã���$n��$lͱȥ",
        "$N����$w��һ����һ�壬����ָ��$n��$l",
        "$N����$wǰһָ��һɨ����������$n��$l",
});

int valid_enable(string usage) { return usage == "blade" || usage == "parry"; }

int valid_learn(object me)
{
        return 1;
}

mapping query_action(object me, object weapon)
{
        return ([ 
                "action": action_msg[random(sizeof(action_msg))], 
                "damage": 120 + random(41), 
                "attack": 60 + random(21),
                "dodge" : 60 + random(21),
                "parry" : 60 + random(21),
                "damage_type" : random(2) ? "����" : "����", 
        ]);
}

int practice_skill(object me)
{
        if ((int)me->query("qi") < 60)
                return notify_fail("��ľ���̫���ˡ�\n");
        if ((int)me->query("neili") < 60)
                return notify_fail("��������������ҵ���\n");
        me->receive_damage("qi", 50);
        me->add("neili", -50);
        return 1;
}


