// by dream
// bingxin-jue.c 冰心决

#include <ansi.h>

inherit FORCE;

int valid_force(string force) { return 1; }       

int query_neili_improve(object me)  
{
        int lvl; 
        lvl = (int)me->query_skill("bingxin-jue", 1); 
        return lvl * lvl * 22 * 15 / 100 / 200; 
}

int valid_enable(string usage) { return usage == "force"; }

int valid_learn(object me)
{
        int lvl = (int)me->query_skill("bingxin-jue", 1);


        if (me->query("gender") == "无性" && lvl > 20)
                return notify_fail("你无根无性，阴阳不调，无法领悟冰心决的精妙之处。\n");

        if ((int)me->query_skill("force") < 200)
                return notify_fail("你的内功火候太浅。\n");

        return ::valid_learn(me);
}

int practice_skill(object me)
{
        return notify_fail("冰心决只能用学(learn)的来增加熟练度。\n");
}

string exert_function_file(string func)
{
        return __DIR__"bingxin-jue/" + func;
}

