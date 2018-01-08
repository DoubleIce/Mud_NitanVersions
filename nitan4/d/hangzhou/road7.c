// road7.c
// Date: Nov.1997 by Venus
#include <room.h>
inherit ROOM;
void create()
{
        set("short", "青石大道");
        set("long", @LONG
大道上游人，或步行，或乘轿，或骑马。个个喜气洋洋的来游西
湖。大道延伸向西边和东北边。朝北走便是上北山。南边则通往西泠
桥。
LONG );
        set("exits", ([
            "northeast" : "/d/hangzhou/road8",
            "north"     : "/d/hangzhou/shanlu8",
            "south"     : "/d/hangzhou/xilingqiao",
            "west"      : "/d/hangzhou/road6",
        ]));
        set("objects", ([
            "/d/hangzhou/npc/youfang" : 1,
        ]));
        set("outdoors", "hangzhou");
//        set("no_clean_up", 0);
        setup();
        replace_program(ROOM);
}

