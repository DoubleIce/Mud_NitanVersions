// quest.c

#include <ansi.h>
 
inherit F_CLEAN_UP;

int main(object me, string arg)
{
        object ob;
        mapping to_kill, to_find;
        mapping killed, finded;
        array tk, tf;
        string msg;
        int i, n;

        ob = MAZE_D->query_maze_mainobj(me);
        if (! ob) ob = FUBEN_D->query_maze_mainobj(me);
        
        if (! ob) return notify_fail("你当前地点没有可以显示的副本任务。\n");
        
        if (! ob->query("quest/quest_name"))
                return notify_fail("你目前还没有领取任何副本任务。\n");

        to_kill = ob->query("quest/to_kill");
        killed = ob->query("quest/killed");
        to_find = ob->query("quest/to_find");
        finded = ob->query("quest/finded");
        
        write("任务名称: " + ob->query("quest/quest_name") + "\n");
        write("任务描述: " + ob->query("quest/quest_desc") + "\n");
        if (mapp(to_kill) && sizeof(to_kill))
        {
                write("杀敌任务进程: \n");    
                msg = "";                  
                tk = keys(to_kill);                
                for (i=0;i<sizeof(tk);i++)
                {
                        if (sizeof(killed) && !undefinedp(killed[tk[i]]))
                                n = killed[tk[i]];
                        else n = 0;
                        msg += tk[i] + ": " + n + "/" + to_kill[tk[i]] + "\n";
                }
                write(msg);
        }
        if (mapp(to_find) && sizeof(to_find))        
        {
                write("寻物任务进程: \n");
                msg = "";
                tf = keys(to_find);              
                for (i=0;i<sizeof(tf);i++)
                {
                        if (sizeof(finded) && !undefinedp(finded[tf[i]]))
                                n = finded[tf[i]];
                        else n = 0;
                        msg += tf[i] + ": " + n + "/" + to_find[tf[i]] + "\n";
                }
                write(msg);
        }
        if (n = ob->query_remove_time()-time())
                 write("副本将在"+CHINESE_D->chinese_period(n)+"后消失。\n"); 
        
        return 1;
}

