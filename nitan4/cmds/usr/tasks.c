 // task.c

#include <ansi.h>
int main(object me, string str)
{
        string output;

        if(me->is_busy())
        return notify_fail("你现在正忙。\n");

        if (! wizardp(me) && (time() - me->query_temp("last_tasks") < 5))
                return notify_fail("系统气喘嘘地叹道：慢慢来 ....\n");  

        if (me->query("jing") < 2)
                return notify_fail("你现在精神状态不佳，还是等会再查吧。\n");

        me->add("jing",-2);

        if (str && str == "count")
        {
                tell_object(me, "你目前已经完成有效TASK使命 " + me->query("task/count") + " 个。\n");
                return 1;
        }

    output = HIR"★ "HIW"泥潭"HIR" ★"HIG" TASK任务 使命榜\n" NOR; 
    output += ""HIW"─────────────────────────────────────\n"NOR"";   
        output += TASK_D->task_list();   
    output += ""HIW"─────────────────────────────────────\n\n"NOR"";   

        me->start_more(output);
        me->set_temp("last_tasks", time());
        return 1;
}

int help(object me)
{
        write(@HELP
指令格式: task
指令格式: task count 查看自己已经完成TASK使命的个数。
相关文件: help tasks

这个指令是用来得知目前的所有使命.

HELP
        );
        return 1;
}

