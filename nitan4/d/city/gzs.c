#include <room.h>
inherit ROOM;

void create()
{
    set("short", "工作室");
        set("long", @LONG
这里是新建的一间工作室，因为老板赶着开工，还没有进行装修。
LONG );
        set("no_fight",1);
    set("exits", ([
        "west"  : "/d/city/beimen",
    ]));
    set("objects", ([
        "/quest/npc/yao" : 1,
        "/d/city/npc/jpl" : 1,
    ]));
    set("no_clean_up", 0);
    setup();
    replace_program(ROOM);
}

