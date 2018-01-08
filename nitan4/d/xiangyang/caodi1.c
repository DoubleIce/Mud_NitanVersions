// Room: /d/xiangyang/caodi1.c
// Date: Jan. 8 1999 by Winder

inherit ROOM;
#include <ansi.h>;

void create()
{
	set("short", "草地");
        set("long", @LONG
这是襄阳城外的草地。蒙古兵进犯以来，这里的百姓全进城了，
蒙古兵驰骋来去，以为牧场，尘土飞扬，甚是嚣张。
LONG );
        set("outdoors", "xiangyang");

	set("exits", ([
		"west"  : "/d/xiangyang/northgate2",
	]));
	set("objects", ([
		"/d/xiangyang/npc/tuolei"   : 1,
		"/d/xiangyang/npc/menggubing" : 2,
	]));
	set("coor/x", -290);
	set("coor/y", -20);
	set("coor/z", 0);
	setup();
	replace_program(ROOM);
}

