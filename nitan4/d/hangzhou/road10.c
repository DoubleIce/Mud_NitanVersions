// road10.c
// Date: Nov.1997 by Venus
#include <room.h>
inherit ROOM;
void create()
{
        set("short", "青石大道");
        set("long", @LONG
沿湖大道旁店铺林立，长街古朴，屋舍鳞次栉比，道上人来车往，
一片太平热闹景象。街的东边是一座酒楼。
LONG );
        set("exits", ([
            "north"     : "/d/hangzhou/road9",
            "south"     : "/d/hangzhou/road11",
            "east"      : "/d/hangzhou/jiulou",
            "west"      : "/d/hangzhou/marryroom",
        ]));
        set("outdoors", "hangzhou");
        set("no_clean_up", 0);
        setup();
        replace_program(ROOM);
}
