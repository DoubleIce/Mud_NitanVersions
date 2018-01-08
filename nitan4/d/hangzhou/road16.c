// road16.c
// Date: Nov.1997 by Venus
#include <room.h>
inherit ROOM;
void create()
{
        set("short", "青石大道");
        set("long", @LONG
大道上游人，或步行，或乘轿，或骑马。个个喜气洋洋的来游西
湖。北边可上雷峰，南边是净慈寺。
LONG );
        set("exits", ([
            "northup" : "/d/hangzhou/xizhaoshan",
            "south"   : "/d/hangzhou/jingcisi",
            "east"    : "/d/hangzhou/road15",
            "west"    : "/d/hangzhou/road20",
        ]));
        set("objects", ([
            "/d/hangzhou/npc/baizhen" : 1,
                "/clone/npc/walker"  : 1, 
        ]));
        set("outdoors", "hangzhou");
//        set("no_clean_up", 0);
        setup();
        replace_program(ROOM);
}
