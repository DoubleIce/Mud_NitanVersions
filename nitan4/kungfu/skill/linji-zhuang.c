// This program is a part of NITAN MudLIB
// linji-zhuang.c 临济十二庄 (emei force)

#include <ansi.h>

inherit FORCE;
int valid_force(string force) { return 1; }

int query_neili_improve(object me)
{
        int lvl;

        if (me->query("sex"))
                return 0;
                
        lvl = (int)me->query_skill("linji-zhuang", 1);
        return lvl / 100 * lvl * 24 * 15 / 200;
}

string *skill_name = ({
        "天字庄",
        "地字庄",
        "之字庄",
        "心字庄",
        "游龙庄",
        "鹤翔庄",
        "旋风庄",
        "飘云庄",
        "大字庄",
        "小字庄",
        "幽字庄",
        "冥字庄",
        "临济十二庄",
});

string *combo_name = ({
        "天地",
        "之心",
        "龙鹤",
        "风云",
        "大小",
        "幽冥",
});

int valid_enable(string usage)
{
        return usage == "force";
}

int valid_learn(object me)
{
        int i, np, nf, nh, ns, ts;
        nf = (int)me->query_skill("force", 1);
        nh = (int)me->query_skill("linji-zhuang", 1);
        np = (int)me->query_skill("mahayana", 1);

        if (me->query("gender") != "女性")
                return notify_fail("你非女子，不能练习临济十二庄。\n");

        if (np <= nh && np < 200)
                return notify_fail("你的大乘涅磐功修为不够，无法领会更高深的临济十二庄。\n");

        if (nf < 40)
                return notify_fail("你的基本内功火候还不够，无法领会临济十二庄。\n");

        return 1;
}

int practice_skill(object me)
{
        return notify_fail("临济十二庄只能用学(learn)的来增加熟练度。\n");
}

string query_skill_name(int level)
{
        if (level < 180) return skill_name[level/15];
        else return skill_name[12];
}

string exert_function_file(string func)
{
        return __DIR__"linji-zhuang/" + func;
}

void skill_improved(object me)
{
        int level = me->query_skill("linji-zhuang",1);
        int o_lvl = me->query("linji_lvl");
        int i;

        if ( level > 180 ) return;

        if ( level/15*15 == level ) {
                tell_object(me, HIG "你对「" + skill_name[level/15-1] + "」已豁然贯通。\n"NOR);
                if (o_lvl < level) {
                        tell_object(me, HIG"顿时你对基本内功的领悟也大大提高。\n"NOR);
                        for (i=0; i< level; i++)                
                        me->improve_skill("force", level);
                }
        }

        if ( level/30*30 == level ) 
        if (o_lvl < level) {
                tell_object(me, HIY"此时你" + combo_name[level/30-1] +
                        "二庄融会贯通，一股柔和的真气周游全身，内力修为更精深了一层。\n"NOR);
                me->add("max_neili", level);
        }
        

        if ( o_lvl < level ) me->set("linji_lvl", level);
                
}

/*
void skill_improved(object me)
{
        switch (me->query_skill("linji-zhuang",1))
        {
        case 30:
                tell_object(me, HIG "你已经把天地庄练成了！\n" NOR );
                break;
        case 60:
                tell_object(me, HIG "你已经把之心庄练成了！\n" NOR );
                break;
        case 90:
                tell_object(me, HIG "你已经把龙鹏庄练成了！\n" NOR );
                break;
        case 120:
                tell_object(me, HIG "你已经把风云庄练成了！\n" NOR );
                break;
        case 150:
                tell_object(me, HIG "你已经把大小庄练成了！\n" NOR );
                break;
        case 180:
                tell_object(me, HIG "你已经把幽冥庄练成了！\n" NOR );
                break;
        }
        return;
}
*/
