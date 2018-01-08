#include <ansi.h>
#include <room.h>

inherit ROOM;

void create()
{
	set("short", "花园");
        set("long", @LONG
这是一条铺的十分平整的石板路，路面被打扫的干干净净南面过
去是个花圆，传来阵阵花香，西面是静修室，东面传来些读书声，看
来那里是书房了。
LONG );
        set("exits",([
		"north" : __DIR__"shilu1",
		"south" : __DIR__"lang2",
	]));

	set("outdoors", "kunlun");
	setup();
	replace_program(ROOM);
}
