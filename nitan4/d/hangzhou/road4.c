// road4.c
// Date: Nov.1997 by Venus
#include <room.h>
inherit ROOM;
void create()
{
        set("short", "青石大道");
        set("long", @LONG
大道上游人，或步行，或乘轿，或骑马。个个喜气洋洋的来游西
湖。往南是洪春桥。大道则延伸向东北边。
LONG );
        set("exits", ([
            "south"     : "/d/hangzhou/hongchunqiao",
            "northeast" : "/d/hangzhou/road5",
        ]));
        set("outdoors", "hangzhou");
        set("no_clean_up", 0);
        setup();
        replace_program(ROOM);
}
