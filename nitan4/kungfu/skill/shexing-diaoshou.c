// This program is a part of NITAN MudLIB
// shexing-diaoshou 蛇形刁手

#include <ansi.h>
#include <combat.h>
inherit SKILL;

string *action_msg = ({
        "$N左掌护胸，右臂微举作蛇形，续而向外疾伸，一式「灵蛇出洞」攻向$n的$l",
        "$N大叫一声使出「虎头蛇尾」，右手虚晃掩饰中；左手从$n意想不到之处疾抓其$l",
        "$N使出「画蛇添足」，双手向$n抓去，同时又无声无息地一脚踢向$n的$l",
        "只见$N跌扑于地，趁着$n向前探视，突然蹦起使出「杯弓蛇影」，向$n连抓几把",
        "$N突然抱头欲逃，但却莫明其妙地滚近$n发出凌厉的攻势，好一招「蛇行鼠窜」",
        "$N一式「蛇鹰互搏」，双手带着嘶嘶破空之声，猛烈迅速地尽往$n上身要害攻击",
        "$N双手徊旋中幻出万道蛇影，一招「万蛇汹涌」，诡异奇玄、铺天盖地推向$n",
        "$N出其不意地使一式「白蛇吐信」，右手食中两指微分，闪电般地往$n的$l猛捅",
        "突见$N双臂柔若无骨地伸缩着，使出「蛇磐青竹」缠住$n，右臂却悄悄地从不可思议处抹到$n的$l",
});
int valid_enable(string usage) { return usage == "hand" ||  usage=="parry"; }

int valid_learn(object me)
{
        if (me->query_temp("weapon") || me->query_temp("secondary_weapon"))
                return notify_fail("练蛇形刁手必须空手。\n");
               
        if (me->query("family/family_name") == "欧阳世家") 
        {
                if ((int)me->query_skill("hamagong",1) < 15)
                        return notify_fail("你的蛤蟆功火候不够，无法学蛇形刁手。\n");
        }
        else if ((int)me->query_skill("huntian-qigong", 1) < 15)
                return notify_fail("你的混天气功火候不够，无法学蛇形刁手。\n");
        if ((int)me->query("max_neili") < 50)
                return notify_fail("你的内力太弱，无法练蛇形刁手。\n");
        return 1;
}

mapping query_action(object me, object weapon)
{
        return ([
                "action": action_msg[random(sizeof(action_msg))],
                "force" : 210 + random(60),
                "attack": 40 + random(10),
                "dodge" : 40 + random(10),
                "parry" : 40 + random(10),
                "damage_type" : random(2)?"瘀伤":"内伤",
        ]);
}

int practice_skill(object me)
{
        if ((int)me->query("qi") < 50)
                return notify_fail("你的体力太低了。\n");
        if ((int)me->query("neili") < 50)
                return notify_fail("你的内力不够练蛇形刁手。\n");
        me->receive_damage("qi", 40);
        me->add("neili", -40);
        return 1;
}
string perform_action_file(string action)
{
        return __DIR__"shexing-diaoshou/" + action;
}

              

