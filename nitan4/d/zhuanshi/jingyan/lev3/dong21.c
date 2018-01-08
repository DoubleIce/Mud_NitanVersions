#include <room.h>
#include <ansi.h>
inherit ROOM;

void create()
{
	set("short", CYN"石洞"NOR);
        set("long", @LONG
这是一个黑漆漆石洞，周围都是坚硬的石壁，前面有条往上的阶
梯。[36m
LONG );
	set("exits", ([
		"east" : __DIR__"dong24",
		"west" : __DIR__"dong25",
                "up" : "/d/migong/lev2/dong20",
                	]));
                set("no_clean_up", 0);
	setup();
	replace_program(ROOM);
}
