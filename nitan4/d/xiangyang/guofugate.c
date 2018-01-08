// Room: /d/xiangyang/guofugate.c
// Date: Jan. 8 1999 by Winder

inherit ROOM;
#include <ansi.h>;
void create()
{
	set("short", "郭府大门");
        set("long", @LONG
一座建筑古朴的大宅院出现在你的眼前。只见门楼高挑，上书两
个大字[1；32m                     郭   府[2；37；0m全真教第二代弟子耶律齐和几
个家丁站在门前接待前来保卫襄阳的各方义士。
LONG );
        set("outdoors", "xiangyang");
	set("exits", ([
		"south" : "/d/xiangyang/westjie1",
		"north" : "/d/xiangyang/guofuyuan",
	]));
	set("objects", ([
		"/d/xiangyang/npc/yelvqi" : 1,
		"/d/xiangyang/npc/jiading" : 2,
	]));
	set("coor/x", -300);
	set("coor/y", -80);
	set("coor/z", 0);
	setup();
	replace_program(ROOM);
}

