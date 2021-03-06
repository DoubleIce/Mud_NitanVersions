// This program is a part of NITAN MudLIB
// liuhe-dao.c 丐帮六合刀法

#include <ansi.h>
inherit SKILL;

mapping *action = ({
([      "action":"$N大喝一声，手中$w大开大阖，连连挥刀使出「呵壁问天」，斩向$n的$l",
        "attack": 55,
        "dodge" : 56,
        "parry" : 54,
        "damage": 120,
        "lvl" : 0,
        "skill_name" : "呵壁问天",
        "damage_type":  "割伤"
]),
([      "action":"$N运刀如风，一招「气盖河山」，刀势霸道之极，向着$n周身各处猛砍猛劈",
        "attack": 60,
        "dodge" : 60,
        "parry" : 65,
        "damage": 130,
        "lvl" : 10,
        "skill_name" : "气盖河山",
        "damage_type":  "割伤"
]),
([      "action":"$N一着「天地乍合」，突然抢进$n近侧，迅猛地驱刀连斩，攻式顿然合成一个圆圈",
        "attack": 60,
        "dodge" : 60,
        "parry" : 55,
        "damage": 140,
        "lvl" : 25,
        "skill_name" : "天地乍合",
        "damage_type":  "割伤"
]),
([      "action":"$N仰天悲笑，随即挥刀斩出一式「离合无常」，$w化为一丝丝寒意，裹向$n$l",
        "attack": 70,
        "dodge" : 65,
        "parry" : 70,
        "damage": 140,
        "lvl" : 35,
        "skill_name" : "离合无常",
        "damage_type":  "割伤"
]),
([      "action":"$N施展「和合六出」绕着$n飞旋，$w带着狂野刀风，凌历无比地劈出六刀",
        "attack": 63,
        "dodge" : 60,
        "parry" : 70,
        "damage": 145,
        "lvl" : 45,
        "skill_name" : "和合六出",
        "damage_type":  "割伤"
]),
([      "action":"$N脸色庄重，挥刀使出「阴阳隔阂」，$w由上而下向$n连劈，犹似一个个焦雷轰顶",
        "attack": 70,
        "dodge" : 70,
        "parry" : 75,
        "damage": 145,
        "lvl" : 60,
        "skill_name" : "阴阳隔阂",
        "damage_type":  "割伤"
]),
});

int valid_enable(string usage) { return usage == "blade" || usage == "parry"; }

int valid_learn(object me)
{
        if ((int)me->query("max_neili") < 100)
                return notify_fail("你的内力不够。\n");
        if ((int)me->query_skill("huntian-qigong", 1) < 20)
                return notify_fail("你的混天气功火候太浅。\n");
                
        return 1;
}

string query_skill_name(int level)
{
        int i;
        for (i = sizeof(action)-1; i >= 0; i--)
                if(level >= action[i]["lvl"])
                        return action[i]["skill_name"];
}

mapping query_action(object me, object weapon)
{
        int i, level, num=0;
        object ob;

        level = (int)me->query_skill("liuhe-dao",1);
        ob = me->select_opponent();
        
        /*
        if (me->query_temp("lianhuan")) 
        {
                num = 1+random(2);
                message_combatd(YEL "\n$N闪电般地劈出凌历的" + chinese_number(num + 1) + "刀。\n" NOR, me);
                for (i = 1; i < num; i++) 
                {
                        if ((me->is_fighting(ob) || ob->is_fighting(me)) && ob->query("qi") > 0)
                                COMBAT_D->do_attack(me, ob, me->query_temp("weapon"));
                        else break;
                }
        }
        */
        
        for (i = sizeof(action); i > 0; i--)
                if (level > action[i-1]["lvl"])
                        return action[NewRandom(i, 20, level/5)];
}

int practice_skill(object me)
{
        object weapon;

        if (! objectp(weapon = me->query_temp("weapon"))
        || (string)weapon->query("skill_type") != "blade")
                return notify_fail("你使用的武器不对。\n");
                
        if ((int)me->query("qi") < 70)
                return notify_fail("你的体力不够练六合刀法。\n");
        if ((int)me->query("neili") < 70)
                return notify_fail("你的内力不够练六合刀法。\n");
                
        me->receive_damage("qi", 60);
        me->add("neili", -60);
        return 1;
}

string perform_action_file(string action)
{
        return __DIR__"liuhe-dao/" + action;
}
