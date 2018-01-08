// bluesea-force.c �Ϻ�����

#include <ansi.h>
inherit FORCE;

string *dodge_msg = ({
        "$n����������$N�Ľ������������ǽ�ϣ�û�а��Ч����\n",
        "$n���һ����һ������ֱ�������Ӳ����������$N��\n",
        "$n����һת��һ�����罫$N������ȫ�����⡣\n",
        "$n��Ȼ��Ц��΢΢�ƶ�����������ʹ$N�Ľ�����֮���塣\n",
});

int query_neili_improve(object me)
{
        int lvl;

        lvl = (int)me->query_skill("bluesea-force", 1);
        return lvl * lvl * 20 * 15 / 100 / 200;
}

mapping *actionf = ({
([      "action":"$N���һ����һָ��������$n��$l�������˷�Բ����ķ�Χ",
        "force" : 500,
        "attack": 150,
        "dodge" : 90,
        "parry" : 88,
        "damage": 170,
        "damage_type":  "����"
]),
([      "action":"$Nһ����ȣ��漴һ����������;ȴ��Ȼһָ����$n��$l",
        "force" : 510,
        "attack": 165,
        "dodge" : 110,
        "parry" : 90,
        "damage": 160,
        "damage_type":  "����"
]),
([      "action":"$N��������������������$n�ļ�ͷ������ʳȴ����$n��$l��",
        "force" : 515,
        "attack": 155,
        "dodge" : 85,
        "parry" : 85,
        "damage": 175,
        "damage_type":  "����"
]),
([      "action":"$N����һ�������������ƣ�˫����������$n��$l",
        "force" : 520,
        "attack": 140,
        "dodge" : 80,
        "parry" : 90,
        "damage": 180,
        "damage_type":  "����"
]),
([      "action":"$N����ԭ�ز�����˫��ƽ�ƣ�һ��������ձ�$n��ȥ",
        "force" : 535,
        "attack": 135,
        "dodge" : 80,
        "parry" : 95,
        "damage": 170,
        "damage_type":  "����"
]),
([      "action":"$N���°��Ͱ��ԣ��������Ī�⣬��������������������$n",
        "force" : 500,
        "attack": 150,
        "dodge" : 85,
        "parry" : 115,
        "damage": 165,
        "damage_type":  "����"
]),
});

mapping *actionw = ({
([      "action":"$N���һ��������$w��������$n�������˷�Բ����ķ�Χ",
        "force" : 450,
        "attack": 170,
        "dodge" : 100,
        "parry" : 110,
        "damage": 200,
        "damage_type":  "����"
]),
([      "action":"$Nһ����ȣ����е�$w�漴��ɨ$n����;ȴ��Ȼ����$n��$l",
        "force" : 460,
        "attack": 165,
        "dodge" : 80,
        "parry" : 110,
        "damage": 220,
        "damage_type":  "����"
]),
([      "action":"$N��������������������$n�ļ�ͷ�����ֵ�$wȴ����$n��$l��",
        "force" : 480,
        "attack": 175,
        "dodge" : 85,
        "parry" : 100,
        "damage": 210,
        "damage_type":  "����"
]),
([      "action":"$N����һ�������������ƣ����е�$w��������$n��$l",
        "force" : 475,
        "attack": 180,
        "dodge" : 75,
        "parry" : 120,
        "damage": 205,
        "damage_type":  "����"
]),
([      "action":"$N����ԭ�ز��������е�$wһ����һ��������ձ�$n��ȥ",
        "force" : 480,
        "attack": 175,
        "dodge" : 80,
        "parry" : 125,
        "damage": 210,
        "damage_type":  "����"
]),
([      "action":"$N���°��ϰ��ԣ��������Ī�⣬���е�$w����������â������$n",
        "force" : 490,
        "dodge" : 160,
        "parry" : 110,
        "damage": 220,
        "damage_type":  "����"
]),
});

string *usage_skills = ({ "finger", "strike", "staff", "dodge",
                          "parry", "force" });

int valid_enable(string usage)
{
        return (member_array(usage, usage_skills) != -1);
}

int valid_force(string force) { return 1; }

int valid_combo(string combo)
{
        return combo == "bluesea-force" ||
               combo == "tanzhi-shentong";
}

int double_attack() { return 1; }

mapping query_action(object me, object weapon)
{
        return weapon ? actionw[random(sizeof(actionw))] :
                        actionf[random(sizeof(actionw))];
}

string query_dodge_msg(string limb)
{
        return dodge_msg[random(sizeof(dodge_msg))];
}

int valid_learn(object me)
{
        int level;
        int i;

        if (count_lt(me->query("combat_exp"), 3000000))
                return notify_fail("������Ϻ��������֮����"
                                   "ƾ�Լ���ս������һʱ��������ᡣ\n");

        if ((int)me->query_skill("martial-cognize", 1) < 50)
                return notify_fail("������Ϻ������������֮������"
                                   "�Լ�����ѧ����ȫȻ�޷����ס�\n");

      if (me->query("character") != "�ĺ�����" &&
          me->query("character") != "��ʿ��˫")
                return notify_fail("�㷢���Ϻ������кݡ�ʽʽ�գ���"
                                   "���������Լ�ʵ����᲻�ˡ�\n");

        if (me->query("con") < 22 && me->query_con() < 63)
                return notify_fail("����ͼ�������������Ϻ�������ȴͻ"
                                   "Ȼ������ǰһ�ڣ������Ǹ��ǲ��ã�"
                                   "������ǿ���С�\n");

	if (me->query("gender") == "����" &&
	    (int)me->query_skill("bluesea-force", 1) > 219)
		return notify_fail("���޸����ԣ�����������������������Ϻ�������\n");

        level = me->query_skill("bluesea-force", 1);

        if ((int)me->query_skill("martial-cognize", 1) < level)
                return notify_fail("������Լ�����ѧ�������ޣ���������������Ϻ�������\n");

        for (i = 0; i < sizeof(usage_skills); i++)
                if (me->query_skill(usage_skills[i], 1) < level)
                        return notify_fail("���" + to_chinese(usage_skills[i]) +
                                           "����⻹�������޷���������������Ϻ�������\n");

        return 1;
}

int practice_skill(object me)
{
        return notify_fail("�Ϻ�����������޷��򵥵�ͨ����ϰ������\n");
}

mixed valid_damage(object ob, object me, int damage, object weapon)
{
        mixed result;
        int ap, dp, mp;

        if ((int)me->query_skill("bluesea-force", 1) < 200
        ||  ! living(me) || (int)me->query("neili") < 500 
        ||  me->query_skill_mapped("parry") != "bluesea-force")
                return;

        mp = ob->query_skill("count", 1);
        ap = ob->query_skill("force") + mp;
        dp = me->query_skill("parry", 1) / 2 +
             me->query_skill("bluesea-force", 1);

        if (ap / 2 + random(ap) < dp)
        {
                me->add("neili", -300);
                result = ([ "damage": -damage ]);

                switch (random(3))
                {
                case 0:
                        result += (["msg" : HIB "$n" HIB "Ĭ���Ϻ�������������סȫ��$N" HIB
                                            "һ�л���$n" HIB "��ֻ�����ִ�����ʯ���󺣣�"
                                            "��о��ȣ���æ�˻ء� \n" NOR]);
                        break;
                case 1:
                        result += (["msg" : HIB "$N" HIB "һ�й�����$n" HIB "ŭ��һ��������"
                                            "���������ΰ����ǽ����$N" HIB "���бƻء�\n" NOR]);
                        break;
                default:
                        result += (["msg" : HIB "$n" HIB "ȫ������������һ�������סȫ���ѽ�$N" HIB "��"
                                            "�н�����ʽ�������֮�⡣\n" NOR]);
                        break;
                }
                return result;
        } else
        if (mp >= 100)
        {
                switch (random(3))
                {
                case 0:
                        result = HIY "$n" HIY "Ĭ���Ϻ���������סȫ������$N" HIY
                                 "��������ޱȣ���Цһ����һ�о���ʵ�ش���$n" HIY
                                 "���ϡ�\n" NOR;
                        break;
                case 1:
                        result = HIY "$n" HIY "���˷�������ͼ��$N" HIY "����ʽ�ƻء�����"
                                 "$N" HIY "��ʽ��Ȼһ�䣬$n" HIY "��ʱһ����ȴ��Ȼ���С�\n" NOR;
                        break;

                default:
                        result = HIY "$n" HIY "һ�ɻ����������$N" HIY "�Ľ���"
                                 "��ʽ����������$N" HIY "���ѿ�ȥ�������飬��Цһ����$N" HIY
                                 "ȴ�����С�\n" NOR;
                        break;
                }
                COMBAT_D->set_bhinfo(result);
         }
}

mixed hit_ob(object me, object victim, int damage_bonus, int factor) 
{
        if (me->is_busy()
           || random(2) == 0
           || ! living(victim)
           || damage_bonus < 120
           || me->query("neili") < 200
           || me->query_skill("bluesea-force", 1) < 250)
        	return 0;


        if (damage_bonus / 2 > victim->query_con())
        {
                me->add("neili", -100);
                victim->receive_wound("qi", (damage_bonus - 88) / 2, me);
                victim->add("neili", -((damage_bonus - random(80)) / 2), me);

                return random(2) ? HIR "$N" HIR "��עȫ�������Ϻ����ΰ�Ϯ��$n" HIR "�����Ѩ��$n" HIR "�����޷��ֵ����������ˣ���Ѫ���£�" NOR:
                                   HIR "$n" HIR "Ӳ��$N" HIR "һ�У�����Է������纣�˰�Ϯ����$n" HIR "�͵��³�һ����Ѫ�������������ˣ�\n" NOR;
        }        
}

int difficult_level()
{
        return 500;
}

string perform_action_file(string action)
{
        return __DIR__"bluesea-force/perform/" + action;
}

string exert_function_file(string action)
{
        return __DIR__"bluesea-force/exert/" + action;
}

