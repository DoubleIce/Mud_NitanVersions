// This program is a part of NITAN MudLIB

#include <maze.h>
#include <ansi.h>

inherit ROOM;

void destruct_me();

void create()
{
    set("short", "�Թ�");
    set("long", @LONG
����һ�����ʯ�ݣ����ܾ�ʯ�ݾ͵�ǽ�ڷ������ĵ���ɫ��â����յ��ͭ
���³�һ�߸ߵĻ��棬Ʈ����˸��żȻ�еƻ����ѵ����죬�����˸е���Ϣ���
�ž��������������������ʯ���̾ͣ���������һ���ɫʯ�������Ŀ�������
����ϸ�ܵ�ͼ�ƣ����˲�������������ǰ�鿴��mazemap��һ����
LONG );
    set("no_clean_up", 1);
    set("no_drop", 1);
    set("no_sleep_room", 1);
    set("born_time", time() );
    
    setup();
}

void init()
{
    object me, room, next_room;
    int xianjing;
    string mazename;
    int damage;
    
    add_action("do_chakan", "mazemap");

    // ����������
    me = this_player();
    room = this_object();
    
    if ( !me ) return;
    
    xianjing = room->query("maze/xianjing");
    if ( !xianjing ) return;
    
    mazename = room->query("maze/mazename");
    if ( !stringp(mazename) ) return;
    
    switch (xianjing)
    {
        case BUSY:
            message_vision(HIR "\n$N����һ�������ˤ������࣬�ò�������ס���ӣ��Ÿо�����Ť���ˣ���ʹ��...\n\n" NOR, me);
            me->start_busy(5);
            break;
        case TRIP:
            message_vision(HIR "\n$Nһ�Ų�����ʲô������������Ҳ�ѳֲ�ס���͵���ǰ������ֻ����һ�����оþûص�...\n\n" NOR, me);
            next_room = MAZE_D->trip_maze(mazename, room);
            if ( objectp(next_room) )
            {
                me->move(next_room);
            }
            break;
        case LOSTMAP:
            message_vision(HIR "\n$Nֻ���ý���һ���������죬��������������İ�ɫʯ������һ��ǿ�⣬����Ѹ��������ȥ...\n\n" NOR, me);
            MAZE_D->lostmap_maze(mazename);
            break;
        case CHANGEMAP:
            MAZE_D->init_maze(mazename);            
            message_vision(HIR "\n$Nһ�Ųȵ���ʲô���������̵̻İѽ�����ȴ�Ѿ�����������Ƶ������ӵ�������...\n" NOR
                + HIR "ֻ�����ܹ�Ӱ�ζ������������ƺ��ڿ����ƶ�����һ�а������������⾰���ƺ������ı䡣\n\n" NOR, me);
            break;
        case WOUND:
            message_vision(HIR "\nֻ����һ���������죬$N����ʶ�ĸϽ����ã�ȴΪʱ����һ֧����ƫ������������$N��\n" NOR
                + HIR "$N��ŭ���ӣ��˿ڴ�ʹ�����飬�����̲�ס��������������\n\n" NOR, me);
            damage = me->query("max_qi");
            damage = damage/10 + random(damage/10) + 1;
            me->receive_wound("qi", damage);
            break;
        default:
            break;
    }
    
    // ��������������ȥ��
    room->delete("maze/xianjing");
    MAZE_D->remove_xianjing(mazename, room);
    
    return;    
}

int clean_up()
{
    if (time() - query("born_time") > MAZE_LIFT_CYCLE*2)
    {
        destruct_me();
        return 0;
    }
    
    return 1;
}

void destruct_me()
{
    object *obs;
    int i, user_num;

    obs = filter_array(all_inventory(), (: userp($1) || playerp($1) :));
    user_num = sizeof(obs);
    if (user_num)
    {
                message("vision", HIW "\n��ͻȻ������Χ��һ�ж��ζ��������𽥻�Ϊ����...\n\n" NOR, this_object());
        for (i = 0; i < user_num; i ++)
        {
            obs[i]->move(ROOM_EXIT_FILE);
            message("vision", "�����Ȼ��һ��������ֻ��" + obs[i]->name() + "���˳�����\n", 
                    environment(obs[i]), ({ obs[i] }));
        }
    }

    destruct(this_object());
    return;
}

int do_chakan(string arg)
{
    object me, room;
    string map = "";
    string mazename;
    
    
    me = this_player();
    if (!me) return 0;
    
    room = this_object();
    mazename = room->query("maze/mazename");
    
    if (!stringp(mazename))
    {
        map = "����ϸ�Ĳ鿴ʯ�壬����ģģ������ʲô��������...\n";
    }
    else
    {
        if (wizardp(me) && !stringp(arg) )
            map = MAZE_D->get_deep_map(mazename, room);
        else
            map = MAZE_D->get_comm_map(mazename, room);
    }

    if (!stringp(map))
    {
        map = "����ϸ�Ĳ鿴ʯ�壬����ģģ������ʲô��������...\n";
    }

    me->start_more(map);
    
    return 1;
}

int valid_leave(object me, string dir)
{
    if (dir == "out" && userp(me) && this_object()->query("exits/out"))
    {
        MAZE_D->check_maze(this_object()->query("maze/mazename"));
    }

    return ::valid_leave(me, dir);
}
