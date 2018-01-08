// xinmo_room.c

#include <ansi.h>
inherit ROOM;

void create()
{
        set("short", HIM "心魔深处" NOR);
        set("long", @LONG
幻境里到处是迷雾弥漫，周边的景物似有似无，虚无缥缈。
LONG );

        set("maze", 1);
        set("no_magic", 1);
        set("virtual_room",1);
        set("no_clean_up", 1);
        set("outdoors", "maze");
        set("objects", ([
                "/d/maze/shadow/npc/shadow": 5,   
                "/d/maze/shadow/npc/xinmo": 1,   
        ]));
	setup();
}

