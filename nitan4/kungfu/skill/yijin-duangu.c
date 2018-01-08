#include <ansi.h>
inherit FORCE;

int valid_enable(string usage)
{
        // return usage == "force" || usage == "parry";
        return usage == "force";
}

int query_neili_improve(object me)
{
        int lvl;

        lvl = (int)me->query_skill("yijin-duangu", 1);
        return lvl * lvl * 15 * 18 / 100 / 200;
}

int valid_force(string force)
{
        return 1;
}

mapping *action = ({
([      "action":"$NĬ���˹��������׽�͹ǵĿھ�����Ϣ����������������һ��"
]),
});

mapping query_action(object me, object weapon)
{
        return action[0];
}


int valid_learn(object me)
{
        if (me->query("gender") == "����" && (int)me->query_skill("yijin-duangu", 1) > 49)
                return notify_fail("���޸����ԣ�����������������������׽�͹��ڹ���\n");

        if (me->query("character") == "������" && (int)me->query("yijin-duangu", 1) > 199)
                return notify_fail("������澭�������ص��׽�͹�����ֺ룬����ٲȻ������"
                                   "�������������ƺ�ֻ��ѧ�����̶ֳȡ�\n");

        if (me->query("character") == "�ĺ�����" && (int)me->query("yijin-duangu", 1) > 169)
                return notify_fail("������澭�������ص��׽�͹�����ֺ룬����ٲȻ������"
                                   "���ĺ������������ƺ�ֻ��ѧ�����̶ֳȡ�\n");

        if (me->query("character") == "���ս�թ" && (int)me->query("yijin-duangu", 1) > 139)
                return notify_fail("������澭�������ص��׽�͹�����ֺ룬����ٲȻ������"
                                   "�����ս�թ�������ƺ�ֻ��ѧ�����̶ֳȡ�\n");
          if (me->query("con") < 30)
                  return notify_fail("������Լ�������ǲ��㣬һʱ����������\n");

        if ((int)me->query_skill("force", 1) < 100)
                return notify_fail("��Ļ����ڹ���򻹲�����������ѧϰ�׽�͹��ڹ���\n");

        if ((int)me->query_skill("martial-cognize", 1) < (int)me->query_skill("yijin-duangu") * 10 / 7)
                return notify_fail("������Լ�����ѧ�������ޣ���������������׽�͹ǡ�\n");

        return ::valid_learn(me);
}

int practice_skill(object me)
{
        return notify_fail("�׽�͹��ڹ�ֻ����ѧ(learn)�������������ȡ�\n");
        if ((int)me->query("qi") < 150)
                return notify_fail("�������̫���ˣ�������ϰ�׽�͹ǡ�\n");

        if ((int)me->query("neili") < 200)
                return notify_fail("�������̫���ˣ�������ϰ�׽�͹ǡ�\n");

        me->receive_damage("qi", 100);
        me->add("neili", -150);
        return 1;
}

/*
mixed valid_damage(object ob, object me, int damage, object weapon)
{
        mapping result;
        int ap, dp, mp;
        int cost;

        if ((int)me->query_skill("yijin-duangu", 1) < 100 ||
            (int)me->query("neili") < 300)
                return;

        cost = damage / 2;
        if (cost > 100) cost = 100;

        mp = ob->query_skill("count", 1);
        ap = ob->query_skill("force", 1) + mp;
        dp = me->query_skill("parry", 1);

        if (ap / 2 + random(ap) < dp)
        {
                me->add("neili", -cost);
                result = ([ "damage": -damage ]);

                switch (random(3))
                {
                case 0:
                        result += (["msg" : HIM"$n���ֽ�����$N��һ�У�ȴ�������ϡ�һ����"
                                            HIM"�·�$n��ֻ���������㡣\n"NOR]);
                        break;
                case 1:
                        result += (["msg" : HIM"$Nһ��ƽʵ�ô���$n���ϣ�Ȼ��$N�о����"
                                            HIM"�޻���һ����˵�����Ĺ��졣\n"NOR]);
                        break;
                default:
                        result += (["msg" : HIM"�ۿ�$N���бƵ�$n��·���ӣ�ȴ��$nû�˹�ͷ"
                                            HIM"�Ƶ�ֱ̯����ȥ��ʹ$N�����޹�������\n"NOR]);
                        break;
                }
                return result;
        }
}
*/

string exert_function_file(string func)
{
        return __DIR__"yijin-duangu/" + func;
}

