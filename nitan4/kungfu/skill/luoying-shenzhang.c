inherit SKILL;
//by dream

mapping *action = ({
([      "action" : "$N右手五指缓缓一收，一式「回风拂柳」，五指忽然拂向$n五处大穴",
        "force"  : 80,
        "attack" : 14,
        "dodge"  : 7,
        "parry"  : 8,
        "damage" : 5,
        "lvl"    : 0,
        "damage_type" : "内伤",
        "skill_name"  : "回风拂柳"
]),
([      "action" : "$N陡然一个轻巧转身，单掌劈落，一式「江城飞花」，拍向$n的头顶",
        "force"  : 91,
        "attack" : 17,
        "dodge"  : 10,
        "parry"  : 13,
        "damage" : 9,
        "lvl"    : 20,
        "damage_type" : "瘀伤",
        "skill_name"  : "江城飞花"
]),
([      "action" : "$N突然跃起，双手连环，运掌如剑，一式「雨急风狂」，攻向$n的全身",
        "force"  : 108,
        "attack" : 22,
        "dodge"  : 17,
        "parry"  : 15,
        "damage" : 12,
        "lvl"    : 40,
        "damage_type" : "瘀伤",
        "skill_name"  : "雨急风狂"
]),
([      "action" : "$N突然抽身而退，一式「流华纷飞」，平身飞起，双掌向$n连拍数掌",
        "force"  : 180,
        "attack" : 33,
        "dodge"  : 13,
        "parry"  : 16,
        "damage" : 28,
        "lvl"    : 60,
        "damage_type" : "瘀伤",
        "skill_name"  : "流华纷飞"
]),
([      "action" : "$N突然抽身跃起，右掌翻滚，一式「彩云追月」抢在左掌前向$n的$l拍去",
        "force"  : 210,
        "attack" : 38,
        "dodge"  : 30,
        "parry"  : 25,
        "damage" : 33,
        "lvl"    : 80,
        "damage_type" : "瘀伤",
        "skill_name"  : "彩云追月"
]),
([      "action" : "$N使一式「白虹经天」，双掌舞出无数圈劲气，一环环向$n的$l斫去",
        "force"  : 310,
        "attack" : 72,
        "dodge"  : 41,
        "parry"  : 55,
        "damage" : 68,
        "lvl"    : 100,
        "damage_type" : "内伤",
        "skill_name"  : "白虹经天"
]),
([      "action" : "$N一式「落英漫天」，双掌在身前疾转，掌花飞舞，铺天盖地直指向$n",
        "force"  : 378,
        "attack" : 84,
        "dodge"  : 41,
        "parry"  : 65,
        "damage" : 103,
        "lvl"    : 120,
        "damage_type" : "瘀伤",
        "skill_name"  : "落英漫天"
]),
//新增三招
([      "action" : "[1;32m$N一式「柳吉祥」，双掌如柳絮般在胸前摆动，顿时一道道暗劲快速冲向$n[2;37;0m",
        "force"  : 400,
        "attack" : 200,
        "dodge"  : 200,
        "parry"  : 200,
        "damage" : 250,
        "lvl"    : 300,
        "damage_type" : "内伤",
        "skill_name"  : "[1;32m柳吉祥[2;37;0m"
]),
([      "action" : "[1;37m$N的落英神掌已修炼至大成，一招「弧月斩」，猛然凌空飞起，当头向$n斩去[2;37;0m",
        "force"  : 500,
        "attack" : 300,
        "dodge"  : 300,
        "parry"  : 300,
        "damage" : 350,
        "lvl"    : 350,
        "damage_type" : "内伤",
        "skill_name"  : "[1;37m弧月斩[2;37;0m"
]),
([      "action" : "[1;36m$N的落英神掌已入返璞归真境界，运起全身内力，一招「碧涛颂」，如海浪般的
                                                                                               
内力向$n涌去，顿时三丈范围内沙石飞旋，眼见$n已无处可逃[2;37;0m",
        "force"  : 850,
        "attack" : 500,
        "dodge"  : 500,
        "parry"  : 500,
        "damage" : 750,
        "lvl"    : 400,
        "damage_type" : "内伤",
        "skill_name"  : "[1;36m碧涛颂[2;37;0m"
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
                return notify_fail("练落英神剑掌必须空手。\n");

        if ((int)me->query_skill("force") < 200)
                return notify_fail("你的基本内功火候不够，无法学落英神剑掌。\n");

        if ((int)me->query("max_neili") < 2000)
                return notify_fail("你的内力太弱，无法练落英神剑掌。\n");

        if ((int)me->query_skill("strike", 1) < (int)me->query_skill("luoying-shenzhang", 1))
                return notify_fail("你的基本掌法水平有限，无法领会更高深的落英神剑掌。\n");

        /*
        if (me->query("character") == "阴险奸诈")
                return notify_fail("学习落英神剑掌需要博大的胸怀，没有此等胸怀是无法领悟的。\n");
        */

        if (me->query("str") < 22)
                return notify_fail("你先天臂力不足，无法修炼落英神剑掌。\n");

        if ((int)me->query_skill("strike", 1) < 200)
                return notify_fail("你的基本掌法不够娴熟，无法修炼落英神剑掌。\n");

        if ((int)me->query_skill("strike", 1) < 200)
                return notify_fail("你的基本掌法不够娴熟，无法修炼落英神剑掌。\n");

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
                return notify_fail("你的体力太低了。\n");

        if ((int)me->query("neili") < 100)
                return notify_fail("你的内力不够练落英神剑掌。\n");

        me->receive_damage("qi", 45);
        me->add("neili", -40);
        return 1;
}

string perform_action_file(string action)
{
        return __DIR__"luoying-shenzhang/" + action;
}

