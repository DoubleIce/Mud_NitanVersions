// faxisi.c
// Date: Nov.1997 by Venus
#include <room.h>
inherit ROOM;
void create()
{
        set("short", "法喜寺");
        set("long", @LONG
法喜寺是天竺三寺中最敞朗深幽的一座。进香的游客不时的进进
出出。往东可达龙井，朝北是下山的路。
LONG );
        set("exits", ([
                "eastdown"  : "/d/hangzhou/shanlu4",
                "northdown" : "/d/hangzhou/shanlu3",
        ]));
        set("objects", ([
            "/d/hangzhou/npc/guest" : 2,
            "/d/hangzhou/npc/seng" : 1,
        ]));
//        set("no_clean_up", 0);
        set("outdoors", "hangzhou");
        setup();
        replace_program(ROOM);
}
