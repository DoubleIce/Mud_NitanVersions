// mazemap.c
#include <ansi.h>
inherit F_CLEAN_UP;

int main(object me, string arg)
{
        int x, y;
        string pname;
        string content, file, str;
        string filename, dir;
        
        if (me->is_busy())
                return notify_fail("你现在正忙。\n");

        if (! wizardp(me) && (time() - me->query_temp("maze/map") < 3))
                return notify_fail("系统气喘嘘地叹道：慢慢来 ....\n");  
        
        if (! environment(me)->query("maze"))
                return notify_fail("这里不是迷宫区域，请用 help here 查看。\n");  
                
        if (me->query("jing") < 5)
                return notify_fail("你现在精神状态不佳，还是等会再查吧。\n");

        me->add("jing", -5);
        me->set_temp("maze/map", time());
        
        file = base_name(environment(me));
        //if (file[0..1]=="/f")
        if (1)
        {
                if (wizardp(me))
                        write(FUBEN_D->query_maze_mainobj(me)->display_deep_map(environment(me)));
                else
                        write(FUBEN_D->query_maze_mainobj(me)->display_common_map(environment(me)));
                return 1;
        }

        pname = file;
        
        while (1)
        {
                int idx = strsrch(pname, "/", -1);

                if(idx == -1)
                        return 0;

                if(idx != 0)
                        pname = pname[0..idx-1];

                if(file_size(pname + ".c") >= 0)
                {
                        filename = pname + ".map";
                        content = read_file(filename);
                        if (!sizeof(content)) return 0;
                        str = file[idx + 1..];
                        if (str == "entry")
                        {
                                for (int i=0; i<10; i++)
                                        content = replace_string(content, sprintf("%d", i), " ");                                       
                                content = replace_string(content, "$HBWHT$  ", "$HBWHT$$BLU$★");
                                write(color_filter(content + "\n"));
                                return 1;
                        }
                        else
                        if (str == "exit")
                        {
                                for (int i=0; i<10; i++)
                                        content = replace_string(content, sprintf("%d", i), " "); 
                                content = replace_string(content, "$HBRED$  ", "$HBRED$$BLU$★");
                                write(color_filter(content + "\n"));
                                return 1;
                        }                         
                        else
                        {        
                                idx = member_array('/', str);
                        
                                if (idx == -1) return 0;
                        
                                if(!sscanf(str[0..idx-1],"%d",x))
                                        return 0;
                                if(!sscanf(str[idx+1..],"%d",y))
                                        return 0;
                                        
                                content = replace_string(content, sprintf("%d%d", x, y), "$BLU$★$NOR$");
                                for (int i=0; i<10; i++)
                                        content = replace_string(content, sprintf("%d", i), " "); 
                                write(color_filter(content + "\n"));
                                return 1;
                        }
                }
                if(! idx)
                        return 0;
        }

        return 1;
}


