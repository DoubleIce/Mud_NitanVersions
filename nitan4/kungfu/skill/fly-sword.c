// This is player's own skill (Write by Lonely@nt2)
// Create by ����(Jianmin) at Tue Oct 21 16:53:53 2008
// ��������(fly-sword.c)

#include <ansi.h>
inherit SKILL;	
		
int is_invent_skill() { return 1; }

mapping *action = ({
// ZHAOSHI : 0
([      "action" : "�һ���,�Ա����۸�����ٶ�������һ�.",
	"attack" : 260,
	"damage" : 260,
	"force" : 260,
	"dodge" : 260,
	"parry" : 260,
	"lvl" : 100,
	"damage_type" : "����",
	"skill_name" : "������"
 ]),
// ZHAOSHI : 1
});

int valid_learn(object me)
{
        object weapon; 
        
        if (! objectp(weapon = me->query_temp("weapon"))
                || (string)weapon->query("skill_type") != "sword") 
                return notify_fail("��ʹ�õ��������ԡ�\n");
                
        if ((int)me->query("max_neili") < 50)
		return notify_fail("�������̫�����޷���" + "��������" + "��\n");
		
        return 1;
}

int valid_enable(string usage) { 
        return usage == "sword" || 
               usage == "parry"; 
}

string query_skill_name(int level)
{
        int i;
        for(i = sizeof(action)-1; i >= 0; i--)
                if(level >= action[i]["lvl"])
                        return action[i]["skill_name"];
}

mapping query_action(object me, object weapon)
{
        int i, level;
        level = (int)me->query_skill("fly-sword",1);
        for(i = sizeof(action); i > 0; i--)
                if(level > action[i-1]["lvl"])
                        return action[NewRandom(i, 20, level/5)];
}

mixed *query_actions() { return action; }

int query_effect_parry(object attacker, object me)
{
        int lvl;

        if (me->query_temp("weapon"))
                return 0;

        lvl = me->query_skill("fly-sword", 1);
        if (lvl < 80)  return 0;
        if (lvl < 200) return 50;
        if (lvl < 280) return 80;
        if (lvl < 350) return 100;
        return 120;
}

int practice_skill(object me)
{
        object weapon; 
        if (!objectp(weapon = me->query_temp("weapon")) || 
                (string)weapon->query("skill_type") != "sword") 
                return notify_fail("��ʹ�õ��������ԡ�\n");	
        
        if( (int)me->query("qi") < 25 )
		return notify_fail("������������ˣ���Ϣһ�������ɡ�\n");
		
	if( (int)me->query("neili") < 3 )
		return notify_fail("������������ˣ���Ϣһ�������ɡ�\n");
		
	me->receive_damage("qi", 25);
	me->add("neili", -3);
	return 1;
} 

mixed hit_ob(object me, object victim, int damage)
{
        mixed result;
        if (damage < 100) return 0;

        if (random(damage) > victim->query_str()) 
        {
                result = ([ "damage" : damage ]);
                result += ([ "msg" : HIW "�����������꡹һ�����죬�ѱ�$N�ı�������ɱ�����ˣ�$n��ʱѪð���ɣ�����\n" NOR ]);

                return result;
        }
}

string perform_action_file(string action) 
{
        return __DIR__ + "fly-sword" + "/" + action; 
}
string query_description()
{
	return
 "" ; 
}
