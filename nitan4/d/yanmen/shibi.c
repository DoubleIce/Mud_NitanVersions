// Create by lonely@NT
#include <ansi.h>
inherit ROOM;

void create()
{
        set("short", "ʯ��"NOR);
        set("long", @LONG
����쵽�����Ρ���Ӫפ�����ˣ�ԶԶ�ؿ��Կ�����Ӫ�ڷ����
��������ʱ�м�ƥ����ɱ��������������ٿ�����Ȼವ�һö�����
��ͷ�Ϸɹ������ǸϿ��뿪�ĺá�
LONG );

        set("no_fly", "1");
        set("exits", ([ /* sizeof() == 5 */   
               "south" :   __DIR__"shance",
               "north" :   __DIR__"luanshi8",
        ]));    

        set("objects", ([

        ]));
    
        setup();
        replace_program(ROOM);
}

