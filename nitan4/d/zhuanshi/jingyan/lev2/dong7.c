#include <room.h>
#include <ansi.h>
inherit ROOM;

void create()
{
	set("short", CYN"石洞"NOR);
        set("long", @LONG
[36m这是一个黑漆漆石洞，周围都是坚硬的石壁。 [2；37；0m
LONG );
	set("exits", ([
		"south" : __DIR__"dong01",
		"north" : __DIR__"dong8",
                	]));
	set("no_clean_up", 0);
	setup();
	replace_program(ROOM);
}
