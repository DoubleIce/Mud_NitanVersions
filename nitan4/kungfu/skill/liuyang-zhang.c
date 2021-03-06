// SKILL liuyang-zhang.c
#include <ansi.h>
#include <combat.h>

inherit SKILL;

int baihong(object me, object victim, int damage);

mapping *action = ({
([	"action" : "$N一招「落日熔金」，左掌叠于右掌之上，劈向$n",
	"force" : 100,
        "attack": 2,
	"dodge" : 30,
        "parry" : 1,
	"damage": 5,
	"lvl"   : 0,
	"skill_name" : "落日熔金",
	"damage_type" : "瘀伤"
]),
([	"action" : "$N一招「安禅制毒龙」，面色凝重，双掌轻飘飘地拍向$n",
	"force" : 130,
        "attack": 8,
	"dodge" : 25,
        "parry" : 3,
	"damage": 30,
	"lvl"   : 20,
	"skill_name" : "安禅制毒龙",
	"damage_type" : "内伤"
]),
([	"action" : "$N一招「日斜归路晚霞明」，双掌幻化一片掌影，将$n笼罩于内。",
	"force" : 160,
        "attack": 12,
	"dodge" : 43,
        "parry" : 4,
	"damage": 35,
	"lvl"   : 30,
	"skill_name" : "日斜归路晚霞明",
	"damage_type" : "瘀伤"
]),

([	"action" : "$N一招「阳关三叠」，向$n的$l连击三掌",
	"force" : 210,
        "attack": 15,
	"dodge" : 55,
        "parry" : 8,
	"damage": 50,
	"lvl"   : 40,
	"skill_name" : "阳关三叠",
        "damage_type" : "瘀伤"
]),
([	"action" : "$N一招「阳春一曲和皆难」，只见一片掌影攻向$n",
	"force" : 250,
        "attack": 22,
	"dodge" : 52,
        "parry" : 0,
	"damage": 30,
	"lvl"   : 60,
	"skill_name" : "阳春一曲和皆难",
	"damage_type" : "瘀伤"
]),

([	"action" : "$N双掌平挥，一招「云霞出海曙」击向$n",
	"force" : 300,
        "attack": 23,
	"dodge" : 65,
        "parry" : 11,
	"damage": 50,
	"lvl"   : 80,
	"skill_name" : "云霞出海曙",
        "damage_type" : "瘀伤"
]),
([	"action" : "$N一招「白日参辰现」，只见一片掌影攻向$n",
	"force" : 310,
        "attack": 28,
	"dodge" : 63,
        "parry" : 5,
	"damage": 80,
	"lvl"   : 100,
	"skill_name" : "白日参辰现",
	"damage_type" : "内伤"
]),

([	"action" : "$N左掌虚晃，右掌一记「云霞出薛帷」击向$n的头部",
	"force" : 330,
        "attack": 25,
	"dodge" : 77,
	"damage": 90,
        "parry" : 12,
	"lvl"   : 120,
	"skill_name" : "云霞出薛帷",
        "damage_type" : "瘀伤"
]),
([	"action" : "$N施出「青阳带岁除」，右手横扫$n的$l，左手攻向$n的胸口",
	"force" : 360,
        "attack": 31,
	"dodge" : 80,
        "parry" : 15,
	"damage": 100,
	"lvl"   : 140,
	"skill_name" : "青阳带岁除",
        "damage_type" : "瘀伤"
]),
([	"action" : "$N施出「阳歌天钧」，双掌同时击向$n的$l",
	"force" : 400,
        "attack": 32,
	"dodge" : 81,
        "parry" : 10,
	"damage": 130,
	"lvl"   : 160,
	"skill_name" : "阳歌天钧",
        "damage_type" : "瘀伤"
])
});

int valid_enable(string usage) { return usage=="parry" || usage=="strike"; }

int valid_combine(string combo) { return combo=="zhemei-shou"; }

int valid_learn(object me)
{
        if ((int)me->query("str") < 30)
                return notify_fail("你研究了半天，感觉膂力有些低，始终无法随意施展。\n");

	if (me->query_temp("weapon") || me->query_temp("secondary_weapon"))
		return notify_fail("练天山六阳掌必须空手。\n");

        if ((int)me->query_skill("force") < 50)
                return notify_fail("你的内功火候不够，无法练六阳掌。\n");

	if ((int)me->query("max_neili") < 200)
		return notify_fail("你的内力太弱，无法练六阳掌。\n");

	if ((int)me->query_skill("strike", 1) < (int)me->query_skill("liuyang-zhang", 1))
		return notify_fail("你的基本掌法水平有限，无法领会更高深的天山六阳掌。\n");

	return 1;
}

mapping query_action(object me, object weapon)
{
	int i, level, busy_time;
	object target = offensive_target(me);
	object victim;
	string *limbs, limb, msg;

	level = (int)me->query_skill("liuyang-zhang", 1);
	victim = me->select_opponent();
	if (!victim)
	{
		for( i = sizeof(action); i > 0; i-- )
			if( level > action[i-1]["lvl"] )
				return action[NewRandom(i, 20, level/5)];
	}
	limbs = victim->query("limbs");
	limb = limbs[random(sizeof(limbs))];
	busy_time = level/20;

	if( random(me->query_temp("lingjiu/baihong")) > 50 || me->query_temp("baihong_attack") ) 
	{
		switch( me->query_temp("baihong_attack") )
		{
			case 1: msg = "不料$N左掌一带，掌力绕过$N的身子，直拍向$p$l";
				break;
			case 2: msg = WHT"谁知$N一掌未竭第二掌又至，连催两重劲，掌力便如长蛇之游，奇诡不可设想"NOR;
				break;
			default: msg = WHT"突然间$N掌力破空，拍向$n"+limb+"，劲风扑面，锋利如刀，转而斜砍$p$l"NOR;
				break;
		}

		me->add_temp("lingjiu/baihong", -1); 
		me->add("neili", -30);

		return ([
			"action": msg,
			"force" : 380+random(120),
			"dodge" : 10,
			"damage": 120+random(80),
			"damage_type":"内伤",
			"post_action": (: baihong :)
			]);
	}

	for( i = sizeof(action); i > 0; i-- )
		if( level > action[i-1]["lvl"] )
			return action[NewRandom(i, 20, level/5)];
}

int practice_skill(object me)
{
	if ((int)me->query("qi") < 70)
		return notify_fail("你的体力太低了。\n");
	if ((int)me->query("neili") < 70)
		return notify_fail("你的内力不够练天山六阳掌。\n");

	me->receive_damage("qi", 61);
	me->add("neili", -57);
	return 1;
}

string perform_action_file(string action)
{
	return __DIR__"liuyang-zhang/" + action;
}

int baihong(object me, object victim, int damage)
{
	int level = (int)me->query_skill("liuyang-zhang", 1)/2;

	me->add_temp("baihong_attack", 1);

	if( damage == RESULT_DODGE && me->query_temp("baihong_attack") < 3 ) 
	{
		me->add_temp("apply/attack", level);

		if( me->query_temp("baihong_attack") == 1 )
			COMBAT_D->do_attack(me, victim, me->query_temp("weapon"), TYPE_QUICK);
		else me->delete_temp("baihong_attack");

		me->add_temp("apply/attack", -level);
		return 1;
	}
	else me->delete_temp("baihong_attack");
	return 1;
}
