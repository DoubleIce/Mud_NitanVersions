// This program is a part of NITAN MudLIB
// mazemanager.c 迷宫管理指令


inherit F_CLEAN_UP;
#include <maze.h>
#include <ansi.h>

int help (object me);

int main(object me,string arg)
{
    string cmd;
    string mazename;
    array mazelist;
    mapping maze;
    int i;
    string msg = "";
    int hei, len;
    mixed line;
    
    if (! SECURITY_D->valid_grant(me, "(wizard)"))
        return 0;

    if (!arg)
    {
        help(me);
        return 1;
    }
    
    if (sscanf(arg,"%s %s",cmd, mazename) != 2)
        cmd = arg;
        
    if (!stringp(mazename))
    {
        if (cmd == "list")
        {
            mazelist = MAZE_D->query_all_maze();
            if (!mazelist) mazelist = ({ });
            {
                msg += sprintf("泥潭现在有%s个迷宫：\n", chinese_number(sizeof(mazelist)) );
                msg += "＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝\n";
                for (i = 0; i < sizeof(mazelist); i ++)
                {
                    msg += sprintf("迷宫名称：%s\n", mazelist[i]);
                }
            }
        }
        else if (cmd == "enable")
        {
            MAZE_D->set_local_show(1);
            msg += "你将迷宫的地图设置为用户可以查看自己所在的位置。\n";
        }
        else if (cmd == "disable")
        {
            MAZE_D->set_local_show(0);
            msg += "你将迷宫的地图设置为用户不可以查看自己所在的位置。\n";
        }
        else
        {
            help(me);
            return 1;
        }
    }
    else
    {
        if (cmd != "list")
        {
            help(me);
            return 1;
        }

        maze = MAZE_D->query_maze(mazename);
        if (!mapp(maze))
            msg += sprintf("并没有找到名称为『%s』的迷宫。\n", mazename);
        else
        {
            msg += sprintf("名称为『%s』的迷宫详细信息如下：\n", mazename);
            msg += "＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝\n";
            msg += sprintf("迷宫对应的NPC：\t/%O\n", maze["boss"]);
            msg += sprintf("迷宫对应的玩家：%s\n", maze["player"]);
            msg += sprintf("迷宫剩余的时间：%s\n", appromix_time( MAZE_LIFT_CYCLE - (time() - maze["born_time"])) );
            msg += sprintf("迷宫的入口：\t/%O\n", maze["entry"]);
            msg += sprintf("迷宫的出口：\t/%O\n", maze["target"]);
            msg += "迷宫地图的模式：";
            switch (maze["map_status"])
            {
                case MAP_COMM:
                    msg += "普通模式\n";
                    break;
                case MAP_DEEP:
                    msg += "详细模式\n";
                    break;
                case MAP_NONE:
                    msg += "失效模式\n";
                    break;
                default:
                    msg += "未知模式\n";
                    break;
            }
            line = maze["deep_map"];
            for (hei = 0; hei < sizeof(line); hei ++)
            {
                for (len = 0; len < sizeof(line[hei]); len ++)
                {
                    msg += line[hei][len];
                }
                msg += "\n";
            }
        }
    }

    me->start_more(msg);
    return 1;
}

int help (object me)
{
        write(@HELP
指令格式 : maze list [迷宫名称]
           maze enable|disable

maze list            可以查看当前游戏中所有的迷宫名称。
maze list 迷宫名称   可以查看指定迷宫的详细信息
maze enable          设置玩家可以在地图中看到自己的位置
maze disable         设置玩家无法在地图中看到自己的位置
HELP );
        return 1;
}
