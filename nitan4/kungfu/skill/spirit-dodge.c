inherit SKILL;

string *dodge_msg = ({
        "$n随风向上飘了一点，刚好避过$N的凌厉攻势。\n",
        "可是$n在空中一个翻腾，躲过了$N这一招。\n"
});

int valid_enable(string usage) { return (usage == "dodge") || (usage == "move"); }

int valid_learn(object me) { return 1; }

string query_dodge_msg(string limb)
{
        return dodge_msg[random(sizeof(dodge_msg))];
}

int practice_skill(object me)
{
        if( (int)me->query("qi") < 40 )
                return notify_fail("你的体力太差了，怎么能象精灵一样在空中飞呢？\n");
        me->receive_damage("qi", 30);
        return 1;
}


