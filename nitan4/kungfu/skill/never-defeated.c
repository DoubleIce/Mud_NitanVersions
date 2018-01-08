// never-defeated.c ������

#include <ansi.h>
inherit FORCE;

string *dodge_msg = ({
        "$n�ƿ�������ǡ�ö����$N�Ĺ�����\n",
        "$n��Ȼ������ֱָ$N���������Ƶ�$Nֻ�ܻ��ء�\n",
        "$n�������ܣ���$N��ʵ��ȫ�������\n",
        "$n����һ�����ԣ��ƺ����⣬ȴ�պö��$N��һ����\n",
});

int query_neili_improve(object me)
{
        int lvl;

        lvl = (int)me->query_skill("never-defeated", 1);
        return lvl * lvl * 20 * 15 / 100 / 200;
}

mapping *action_default = ({
([      "action" : "$N���ƺ��������裬�ƽ������Ƶ�����׽��������$n������ȥ",
        "force" : 410,
        "attack": 150,
        "dodge" : 70,
        "parry" : 120,
        "damage": 225,
        "damage_type":  "����"
]),
([      "action":"$N���е�$wͻ������ɭ�ϣ�����ǧ���������۶�������ɨ$n",
        "force" : 410,
        "attack": 160,
        "dodge" : 85,
        "parry" : 110,
        "damage": 210,
        "damage_type":  "����"
]),
([      "action":"$N�������е�$w������$n�ҿ����ң�û�а���·�",
        "force" : 430,
        "attack": 170,
        "dodge" : 70,
        "parry" : 130,
        "damage": 205,
        "damage_type":  "����"
]),
([      "action":"$N����$w�û���һ��һ��ԲȦ���ƺ�Ҫ��$n��Χ",
        "force" : 425,
        "attack": 160,
        "dodge" : 65,
        "parry" : 125,
        "damage": 190,
        "damage_type":  "����"
]),
([      "action":"$N��Ц��ת$w������һָ���ĵ��黨ָ֮�⣬����$n��$l",
        "force" : 530,
        "attack": 176,
        "dodge" : 75,
        "parry" : 115,
        "damage": 200,
        "damage_type":  "����"
]),
([      "action":"$N��̾һ������$w���ֵݳ������Լ�Ҳ��֪��Ҳ��������",
        "force" : 440,
        "attack": 170,
        "dodge" : 80,
        "parry" : 125,
        "damage": 210,
        "damage_type":  "����"
]),
([      "action":"$N��ɫ���أ�$w�����������Һ�ɨ��Ю�������֮�Ʊ���$n",
        "force" : 410,
        "attack": 160,
        "dodge" : 95,
        "parry" : 120,
        "damage": 220,
        "damage_type":  "����"
]),
([      "action":"$N����$w�������籩�꣬���������з���$n��$l�����Ա�$n����",
        "force" : 420,
        "attack": 150,
        "dodge" : 95,
        "parry" : 135,
        "damage": 200,
        "damage_type":  "����"
]),
([      "action":"$NͻȻ���������е�$w��Ȼ��$n�����Ҵ�����",
        "force" : 410,
        "attack": 165,
        "dodge" : 85,
        "parry" : 125,
        "damage": 235,
        "damage_type":  "����"
]),
([      "action":"$N��$w����һ�ڣ�$n�����Լ���$wײ�����������֮����ʵ�����Ѳ�",
        "force" : 430,
        "attack": 180,
        "dodge" : 75,
        "parry" : 110,
        "damage": 225,
        "damage_type":  "����"
]),
([      "action":"$N���е�$w�����ƣ�ȴ�ƻ򵶷����ּ��ӹ���֮�⣬��$nѣĿ",
        "force" : 420,
        "attack": 175,
        "dodge" : 85,
        "parry" : 130,
        "damage": 220,
        "damage_type":  "����"
]),
});

mapping *action_whip = ({
([      "action" : "$N���ƺ��������裬$w�仯�޳���׽��������$n������ȥ",
        "force" : 430,
        "attack": 180,
        "dodge" : 75,
        "parry" : 115,
        "damage": 225,
        "damage_type": "����"
]),
([      "action":"$N���е�$wͻ������ɭ�ϣ�����ǧ���������۶�����$w�������һ���ɨ$n",
        "force" : 410,
        "attack": 160,
        "dodge" : 85,
        "parry" : 125,
        "damage": 210,
        "damage_type": "����"
]),
([      "action":"$N�������е�$w����������һ�����$n�ҿ����ң�û�а���·�",
        "force" : 440,
        "attack": 175,
        "dodge" : 80,
        "parry" : 125,
        "damage": 205,
        "damage_type": "����"
]),
([      "action":"$N����$w�û���һ��һ��ԲȦ���ƺ�Ҫ��$n���Ű�Χ",
        "force" : 425,
        "attack": 160,
        "dodge" : 65,
        "parry" : 125,
        "damage": 190,
        "damage_type": "����"
]),
([      "action":"$N��Ц��ת$w������һָ���ĵ��黨ָ֮�⣬����$n��$l",
        "force" : 510,
        "attack": 180,
        "dodge" : 70,
        "parry" : 120,
        "damage": 200,
        "damage_type": "����"
]),
});

string *usage_skills = ({ "sword", "blade", "dagger",
                          "staff", "hammer", "club", "whip",  
                          "dodge", "parry", "force", "throwing" });

int valid_enable(string usage)
{
        return (member_array(usage, usage_skills) != -1);
}

int valid_combo(string combo)
{
        return combo == "never-defeated";
}

int valid_force(string force) { return 1; }

int double_attack() { return 1; }

mapping query_action(object me, object weapon)
{
        switch (weapon ? weapon->query("skill_type") : "default")
        {
        case "whip":
                return action_whip[random(sizeof(action_whip))];
        default:
                return action_default[random(sizeof(action_default))];
        }
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
                return notify_fail("����ò��������֮����"
                                   "ƾ�Լ���ս������һʱ��������ᡣ\n");

        if ((int)me->query_skill("martial-cognize", 1) < 50)
                return notify_fail("����ò����񹦹�����£���"
                                   "�Լ�����ѧ����ȫȻ�޷����ס�\n");

        if (me->query("character") != "������" &&
            me->query("character") != "��ʿ��˫")
                return notify_fail("��ѧ�˰��죬���ֲ����񹦹Źֵ�"
                                   "�������ϳ����������޷���ᡣ");

        if (me->query("int") < 22)
                return notify_fail("����ò����񹦹�����£���"
                                   "���Լ��������������⡣\n");

	if (me->query("gender") == "����" &&
	    (int)me->query_skill("never-defeated", 1) > 239)
		return notify_fail("���޸����ԣ���������������������Ĳ����񹦡�\n");

        level = me->query_skill("never-defeated", 1);

        if ((int)me->query_skill("martial-cognize", 1) < level)
                return notify_fail("������Լ�����ѧ�������ޣ�������������Ĳ����񹦡�\n");

        if (me->query_skill("force", 1) < level)
                return notify_fail("��Ի����ڹ������⻹�������޷�����"
                                   "��������Ĳ����񹦡�\n");

        if (me->query_skill("parry", 1) < level)
                return notify_fail("��Ի����мܵ����⻹�������޷�����"
                                   "��������Ĳ����񹦡�\n");

        if (me->query_skill("dodge", 1) < level)
                return notify_fail("��Ի����Ṧ�����⻹�������޷�����"
                                   "��������Ĳ����񹦡�\n");

        if (me->query_skill("sword", 1) < level)
                return notify_fail("��Ի������������⻹�������޷�����"
                                   "��������Ĳ����񹦡�\n");

        if (me->query_skill("blade", 1) < level)
                return notify_fail("��Ի������������⻹�������޷�����"
                                   "��������Ĳ����񹦡�\n");

        if (me->query_skill("whip", 1) < level)
                return notify_fail("��Ի����޷������⻹�������޷�����"
                                   "��������Ĳ����񹦡�\n");

        if (me->query_skill("throwing", 1) < level)
                return notify_fail("��Ի������������⻹�������޷�����"
                                   "��������Ĳ����񹦡�\n");

        return 1;
}

int practice_skill(object me)
{
        return notify_fail("�����񹦲�����޷��򵥵�ͨ����ϰ������\n");
}

int difficult_level()
{
        return 500;
}
mixed valid_damage(object ob, object me, int damage, object weapon) 
{ 
        mixed result; 
        int ap, dp, mp; 
        object m_weapon; 
        
        if ((int)me->query_skill("never-defeated", 1) < 200 
        ||  ! (m_weapon = me->query_temp("weapon")) 
        ||  ! living(me) 
        ||  me->query_skill_mapped("parry") != "never-defeated") 
                return; 
        
        mp = ob->query_skill("count", 1); 
        ap = ob->query_skill("parry") + mp; 
        dp = me->query_skill("parry", 1) / 2 + 
        me->query_skill("never-defeated", 1); 
        
        if (ap / 2 + random(ap) < dp) 
        { 
                result = ([ "damage": -damage ]); 

                switch (random(6))
                {
                case 0:
                        result += (["msg" : HIC "$n" HIC "��������$N�Ĺ��ƣ���������Թ�Ϊ�ء�"
                                            "$N���Ʊ��ƣ���о��ȣ���ʱ�����ٳ���\n"
                                            "$n����һָ������ԴԴ����������$N����������\n" NOR]);
                        COMBAT_D->do_attack(me, ob, me->query_temp("weapon")); 
                        COMBAT_D->do_attack(me, ob, me->query_temp("weapon")); 
                        COMBAT_D->do_attack(me, ob, me->query_temp("weapon")); 
                        break;
                case 1:
                        result += (["msg" : HIC "$n" HIC "�ٽ��������������ش���$N��������"
                                            "$N����������������$N������֮����\n" NOR]);
                        COMBAT_D->do_attack(me, ob, me->query_temp("weapon")); 
                        break;
                case 2:
                        result += (["msg" : HIC "$n" HIC "�ὣ�ش̣��������$N��������"
                                            "$N���ò��������أ�����һ�μ����˳�������\n" NOR]);
                        break;
                case 3: 
                        result += (["msg" : HIC "ȴ��$n" HIC "������ǰ����ʽֱָ$P" HIC 
                                            "���ڣ���ʽѸ���ޱȣ�ʹ��$N" HIC "��������" 
                                            "��\n" NOR]); 
                        break; 
                case 4: 
                        result += (["msg" : HIC "$n" HIC "ͻȻһ������$N" HIC "����һ��" 
                                            "ȴ�����������ţ�$N" HIC "��ʱ�����޴룬��" 
                                            "�Ʋ�������ͣ��������\n" NOR]); 
                        break; 
                default: 
                        result += (["msg" : HIC "$n" HIC "�ۼ����޿ɱܣ���Ȼ����ͬ���ھ�����������$N˫�ۣ�"
                                            "��Ȼ�������ϵؽ�$N�Ĺ���ֹס��\n" NOR]);
                        break;
                }       

                return result; 
        } else 
        if (mp >= 100) 
        { 
                switch (random(3)) 
                { 
                case 0: 
                        result = HIY "$n" HIY "һ�����е�" + m_weapon->name() + 
                                 HIY "���й�ֱ��һ��ͦ��������$N" HIY "���и���" 
                                 "����Ϯ$n" HIY "��\n" NOR; 
                        break; 
        
                case 1: 
                        result = HIY "$n" HIY "����" + m_weapon->name() + "����" 
                                 "��" HIY "��ָ��$N" HIY "�����е�����������$N" 
                                 HIY "����һ�䣬�������̲���Ϊ������\n" NOR; 
                        break; 
        
                default: 
                        result = HIY "$n" HIY "����" + m_weapon->name() + HIY 
                                 "���任���ֽ��У�Ȼ��$N" HIY "��Ҳ�������ٴι�" 
                                 "����˿������$n" HIY "���Ի�\n"  NOR; 
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
           || me->query_skill("never-defeated", 1) < 250)
        	return 0;


        if (damage_bonus / 2 > victim->query_dex())
        {
                me->add("neili", -100);
                victim->receive_wound("qi", (damage_bonus - 88) / 2, me);
                victim->add("neili", -((damage_bonus - random(80)) / 2), me);

                return HIR "������$N" HIR "��������һ��Ϯ��$n" HIR "��$n" HIR "�����޷��ֵ����������ˣ���Ѫ���£�\n" NOR;
        }        
}

string perform_action_file(string action)
{
        return __DIR__"never-defeated/perform/" + action;
}

string exert_function_file(string action)
{
        return __DIR__"never-defeated/exert/" + action;
}

