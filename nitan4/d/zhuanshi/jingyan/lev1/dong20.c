#include <room.h>
#include <ansi.h>
inherit ROOM;

void create()
{
	set("short", CYN"石洞"NOR);
        set("long", @LONG
[36m这是一个黑漆漆石洞，周围都是坚硬的石壁，左面有阶梯似乎可
以一直往下去。 [2；37；0m
LONG );
	set("exits", ([
		"north" : __DIR__"dong19",
		"south" : __DIR__"dong10",
                "down" : "/d/jingyan/lev2/dong1"
                	]));
	set("no_clean_up", 0);
	setup();
	replace_program(ROOM);
}
