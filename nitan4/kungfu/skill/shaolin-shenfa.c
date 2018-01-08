// shaolin-shenfa.c 少林身法
// modified by Venus Oct.1997

inherit SKILL;

string *dodge_msg = ({
        "$n一式「一苇渡江」，前后脚脚尖脚跟相靠，身体如行云流水般滑出丈余。\n",
        "$n一式「雨燕掠波」，双臂前伸，全身贴地平飞，顿时闪过了$N的凌厉攻势。\n",
        "$n一式「移步换形」，足不动，手不抬，一转眼间便绕到了$N的身后。\n",
        "$n一式「分身化影」，一转身间，四面八方飘动着无数个$n的身影，令$N手无足措。\n",
        "$n一式「孤骛落日」，全身笔直，拔地而起，在半空中一转，已落到几丈远的地方。\n",
        "$n一式「鸿雁双飞」，两臂鹏举如翼，在剌剌风声中，从$N头顶横跃而过。\n",
        "$n一式「苍龙出水」，双脚点地，全身化为一道白影，急速绕着$N打了几转。\n",
        "$n一式「稚凤归巢」，身体如陀螺般急转，气流形成一个个漩涡，令$N陷身其间，动弹不得。\n",
});

int valid_enable(string usage)
{
    return usage == "dodge" || usage == "move";
}

int valid_learn(object me)
{
    return 1;
}

string query_dodge_msg(string limb)
{
    return dodge_msg[random(sizeof(dodge_msg))];
}

int practice_skill(object me)
{
    if( (int)me->query("qi") < 50 )
        return notify_fail("你的体力太差了，不能练少林身法。\n");

    me->receive_damage("qi", 40);
    return 1;
}

/*
mixed valid_damage(object ob, object me, int damage, object weapon)
{
        mixed result;
        int ap, dp, mp;

        if ((int)me->query_skill("shaolin-shenfa", 1) < 100 ||
            ! living(me))
                return;

        mp = ob->query_skill("martial-cognize", 1);
        ap = ob->query_skill("force") + mp;
        dp = me->query_skill("dodge", 1) / 2 +
             me->query_skill("shailin-shengfa", 1);

        // 一个经典的算法
        if (ap / 2 + random(ap) < dp)
        {
                result = ([ "damage": -damage ]);
                // 去掉所有的伤害写法

                switch (random(3))
                {
                case 0:
                        result += (["msg" : HIC "$n" HIC "一式「稚凤归巢」，身体如陀螺般急转，气流形成一个个漩涡，令$N陷身其间，动弹不得。\n" NOR]);
                        if (! ob->is_busy())
                        ob->start_busy(random(3)); 
                        break;

                case 1:
                        result += (["msg" : HIC "$n" HIC "一式「一苇渡江」，前后脚脚尖脚跟相靠，身体如行云流水般滑出丈余。\n" NOR]);
                        if (! ob->is_busy())
                        ob->start_busy(random(1)); 
                        break;

                default:
                        result += (["msg" : HIC "$n" HIC "一式「分身化影」，一转身间，四面八方飘动着无数个$n的身影，令$N手无足措。\n" NOR]);
                        break;
                }
                return result;
        }
}
*/
string perform_action_file(string action)
{
        return __DIR__"shaolin-shenfa/" + action;
}

