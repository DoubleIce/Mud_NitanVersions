// Room: /huanghe/jingyuan.c
// Java Sep. 22 1998

#include <room.h>

inherit ROOM;

void create()
{
	set("short", "靖远");
        set("long", @LONG
靖远是个不大不小的城镇，黄沙在离城四十里的地方被一排排的
钻天白杨树给挡住了。因此这里有了一块较大的绿洲，聚集了不少从
别处来的移民。这些白杨据说是当年唐朝李靖赶走了突厥后在这里屯
兵时所种。这也是靖远得名的由来。西边不远就是黄河，南面是一大
片沙漠。
LONG );
	set("exits", ([
		"north"     : __DIR__"hongshanxia",
		"south"     : __DIR__"shamo",
	]));
	set("no_clean_up", 0);
	set("outdoors", "huanghe");
	set("coor/x", -10);
	set("coor/y", 140);
	set("coor/z", 0);
	setup();
	replace_program(ROOM);
}

