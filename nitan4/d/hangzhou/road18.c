// road18.c
// Date: Nov.1997 by Venus
#include <room.h>
inherit ROOM;
void create()
{
        set("short", "青石大道");
        set("long", @LONG
大道上游人，或步行，或乘轿，或骑马。个个喜气洋洋的来游西
湖。大道伸向东北和南两边，往西是石屋洞。
LONG );
        set("exits", ([
            "northeast" : "/d/hangzhou/road19",
            "west"      : "/d/hangzhou/shiwudong",
            "south"     : "/d/hangzhou/road17",
            "east"      : "/d/hangzhou/yuhuangshan",
        ]));
        set("outdoors", "hangzhou");
        set("no_clean_up", 0);
        setup();
        replace_program(ROOM);
}
