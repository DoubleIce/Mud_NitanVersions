// This program is a part of NITAN MudLIB
// mazemanager.c �Թ�����ָ��


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
                msg += sprintf("��̶������%s���Թ���\n", chinese_number(sizeof(mazelist)) );
                msg += "������������������������������������\n";
                for (i = 0; i < sizeof(mazelist); i ++)
                {
                    msg += sprintf("�Թ����ƣ�%s\n", mazelist[i]);
                }
            }
        }
        else if (cmd == "enable")
        {
            MAZE_D->set_local_show(1);
            msg += "�㽫�Թ��ĵ�ͼ����Ϊ�û����Բ鿴�Լ����ڵ�λ�á�\n";
        }
        else if (cmd == "disable")
        {
            MAZE_D->set_local_show(0);
            msg += "�㽫�Թ��ĵ�ͼ����Ϊ�û������Բ鿴�Լ����ڵ�λ�á�\n";
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
            msg += sprintf("��û���ҵ�����Ϊ��%s�����Թ���\n", mazename);
        else
        {
            msg += sprintf("����Ϊ��%s�����Թ���ϸ��Ϣ���£�\n", mazename);
            msg += "��������������������������������������������������������\n";
            msg += sprintf("�Թ���Ӧ��NPC��\t/%O\n", maze["boss"]);
            msg += sprintf("�Թ���Ӧ����ң�%s\n", maze["player"]);
            msg += sprintf("�Թ�ʣ���ʱ�䣺%s\n", appromix_time( MAZE_LIFT_CYCLE - (time() - maze["born_time"])) );
            msg += sprintf("�Թ�����ڣ�\t/%O\n", maze["entry"]);
            msg += sprintf("�Թ��ĳ��ڣ�\t/%O\n", maze["target"]);
            msg += "�Թ���ͼ��ģʽ��";
            switch (maze["map_status"])
            {
                case MAP_COMM:
                    msg += "��ͨģʽ\n";
                    break;
                case MAP_DEEP:
                    msg += "��ϸģʽ\n";
                    break;
                case MAP_NONE:
                    msg += "ʧЧģʽ\n";
                    break;
                default:
                    msg += "δ֪ģʽ\n";
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
ָ���ʽ : maze list [�Թ�����]
           maze enable|disable

maze list            ���Բ鿴��ǰ��Ϸ�����е��Թ����ơ�
maze list �Թ�����   ���Բ鿴ָ���Թ�����ϸ��Ϣ
maze enable          ������ҿ����ڵ�ͼ�п����Լ���λ��
maze disable         ��������޷��ڵ�ͼ�п����Լ���λ��
HELP );
        return 1;
}
