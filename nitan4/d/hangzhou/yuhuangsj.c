// yuhuangsj.c
// Date: Nov.1997 by Venus
#include <room.h>
inherit ROOM;
void create()
{
        set("short", "玉皇山脚");
        set("long", @LONG
只见往上的山路曲折蜿延。山路旁有一座小六角亭，几个游人正
在亭里歇脚。东北边是一条青石大道，往西是上山的路。
LONG );
        set("exits", ([
            "northeast" : "/d/hangzhou/road15",
            "westup"    : "/d/hangzhou/shanlu7",
        ]));
        set("objects", ([
            "/d/hangzhou/npc/honghua1" : 2,
        ]));
//        set("no_clean_up", 0);
        set("outdoors", "hangzhou");
        setup();
        replace_program(ROOM);
}
