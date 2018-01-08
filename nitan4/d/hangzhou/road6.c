// road6.c
// Date: Nov.1997 by Venus
#include <room.h>
inherit ROOM;
void create()
{
        set("short", "青石大道");
        set("long", @LONG
大道上游人，或步行，或乘轿，或骑马。个个喜气洋洋的来游西
湖。大道延伸向东西两边。南边则通往苏堤。北边是岳王庙。
LONG );
        set("exits", ([
            "north"     : "/d/hangzhou/yuelang",
            "south"     : "/d/hangzhou/suti1",
            "west"      : "/d/hangzhou/road5",
            "east"      : "/d/hangzhou/road7",
        ]));
        set("objects" , ([
            "/d/hangzhou/npc/liumang" :4,
            "/d/hangzhou/npc/liumangtou" :1,
        ]));
        set("outdoors", "hangzhou");
//        set("no_clean_up", 0);
        setup();
        replace_program(ROOM);
}
