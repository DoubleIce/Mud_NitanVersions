#include <ansi.h>
#include <room.h>

inherit ROOM;

void create()
{
	set("short", "长廊");
        set("long", @LONG
这是一条长廊，连接前厅和客房，不断看见各种打扮的江湖人士
走过，看过廊外，是一片青色的树林，幽静雅致，只听见不断传来的
鸟鸣声。
LONG );
        set("exits",([
		"west" : __DIR__"qianting",
		"east" : __DIR__"keting1",
	]));

	set("outdoors", "kunlun");
	setup();
	replace_program(ROOM);
}
