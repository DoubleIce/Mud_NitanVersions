// This program is a part of NITAN MudLIB
// jingang-chu.c, 金刚降魔杵

inherit SKILL;

string *action_msg = ({
        "$N神色庄严，口宣佛号，使出一招「金刚再世」，手中$w扫向$n的$l",
        "$N满面怒容，口中大喝，大步踏上一式「金刚伏魔」，$w朝着$n当头砸下",
        "$N一招「金刚宣法」，口中念念有词，骤然眼放异光，抡起手中$w横扫$n的$l",
        "$N一招「引趣众生」，左臂弯夹$w，右展立，呼心金咒，单臂挥$w击向$n的$l",
        "$N一式「歌舞阎罗」，口唱轮回经，跨腿飞跳，$w首尾来回击向$n",
        "忽然间$N一脸悲珉之色，手中$w画个半弧使出「浮游血海」，勾向$n的$l",
        "$N一式「驱鬼御魔」，口中念着六字真言，把$w舞成一片黄雾，将$n罩在中央",
        "$N闭目运气鼓足内力，暴喝一声佛号施展「荡魔除妖」，手中$w飞云掣电般直射向$n的$l",
});

int valid_enable(string usage) { return (usage == "staff") || (usage == "parry"); }

int valid_learn(object me)
{
        if ((int)me->query("max_neili") < 80)
                return notify_fail("你的内力不够。\n");
                
        if ((int)me->query_skill("staff", 1) < 
            (int)me->query_skill("jingang-chu", 1))
                return notify_fail("你的基本杖法火候太浅。\n");
        
        return 1;
}

mapping query_action(object me, object weapon)
{
        return ([
                "action": action_msg[random(sizeof(action_msg))], 
                "damage": 120 + random(30), 
                "attack": 40 + random(10), 
                "dodge" : 40 + random(10), 
                "parry" : 40 + random(10), 
                "post_action":  (: call_other, "/adm/daemons/weapond.c", "bash_weapon" :),
                "damage_type" : random(2)?"挫伤":"瘀伤", 
        ]); 
}

int practice_skill(object me)
{
        object weapon;

        if (!objectp(weapon = me->query_temp("weapon"))
        ||  (string)weapon->query("skill_type") != "staff")
                return notify_fail("你使用的武器不对。\n");
        if (me->query_str() < 20)
                return notify_fail("你的臂力不够练金刚降魔杵。\n");
        if ((int)me->query("qi") < 50)
                return notify_fail("你的体力不够练金刚降魔杵。\n");
        if ((int)me->query("neili") < 50)
                return notify_fail("你的内力不够练金刚降魔杵。\n");
        me->receive_damage("qi", 40);
        me->add("neili", -40);
}

string perform_action_file(string action)
{
        return __DIR__"jingang-chu/" + action;
}

