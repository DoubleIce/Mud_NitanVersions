// fajingsi.c
// Date: Nov.1997 by Venus
#include <room.h>
inherit ROOM;
void create()
{
        set("short", "法镜寺");
        set("long", @LONG
法镜寺建在小溪旁，格外的幽雅。进香的游客不时的进进出出。
南上往中天竺。朝北是下山的路。
LONG );
        set("exits", ([
                "southup"   : "/d/hangzhou/shanlu2",
                "northdown" : "/d/hangzhou/shanlu1",
        ]));
        set("objects", ([
           "/d/hangzhou/npc/shami" : 1,
           "/d/hangzhou/npc/guest" : 1,
        ]));
//        set("no_clean_up", 0);
        set("outdoors", "hangzhou");
        setup();
        replace_program(ROOM);
}
