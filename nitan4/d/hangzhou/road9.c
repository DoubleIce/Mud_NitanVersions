// road9.c
// Date: Nov.1997 by Venus
#include <room.h>
inherit ROOM;
void create()
{
        set("short", "青石大道");
        set("long", @LONG
大道上游人，或步行，或乘轿，或骑马。个个喜气洋洋的来游西
湖。大道延伸向西边。断桥在大道的西南边。南边则是另一条大道。
LONG );
        set("exits", ([
            "west"      : "/d/hangzhou/road8",
            "south"     : "/d/hangzhou/road10",
            "southwest" : "/d/hangzhou/duanqiao",
        ]));
        set("outdoors", "hangzhou");
        set("no_clean_up", 0);
        setup();
        replace_program(ROOM);
}
