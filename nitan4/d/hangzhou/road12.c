// road12.c
// Date: Nov.1997 by Venus
#include <room.h>
inherit ROOM;
void create()
{
        set("short", "青石大道");
        set("long", @LONG
沿湖大道旁店铺林立，长街古朴，屋舍鳞次栉比，道上人来车往，
一片太平热闹景象。街东边是一古朴书院，书院里不时传来朗朗的笑
声。西面就是大名鼎鼎的无极帮杭州分部了。
LONG );
        set("exits", ([
            "north"     : "/d/hangzhou/road11",
            "south"     : "/d/hangzhou/road13",
            "east"      : "/d/hangzhou/shuyuan",
        "west"       : "/d/hangzhou/wjb_hzfb",
        ]));
        set("objects", ([
            "/d/hangzhou/npc/likexiu" : 1,
            "/d/hangzhou/npc/qingbing" : 4,
        ]));
        set("outdoors", "hangzhou");
//        set("no_clean_up", 0);
        setup();
        replace_program(ROOM);
}
