// road15.c
// Date: Nov.1997 by Venus
#include <room.h>
inherit ROOM;
void create()
{
        set("short", "青石大道");
        set("long", @LONG
大道上游人，或步行，或乘轿，或骑马。个个喜气洋洋的来游西
湖。东北和西边各是一条大道。西南边是上玉皇山的山路。
LONG );
        set("exits", ([
            "northeast" : "/d/hangzhou/road14",
            "southwest" : "/d/hangzhou/yuhuangsj",
            "west"      : "/d/hangzhou/road16",
        ]));
        set("no_clean_up", 0);
        set("outdoors", "hangzhou");
        setup();
        replace_program(ROOM);
}
