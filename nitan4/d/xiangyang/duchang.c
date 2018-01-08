// Room: /d/xiangyang/duchang.c
// Date: Jan. 8 1999 by Winder

inherit ROOM;

void create()
{
	set("short", "赌场");
        set("long", @LONG
这里本是襄阳最大的赌场。可是大战当前，为免守军军心动摇、
军纪败坏，郭大侠早已下令关闭了赌场。门可罗雀的大院，可以想象
当时的规模，闲置破败的赌具，也不知道在无声地诉说什么。
LONG );
	set("no_clean_up", 0);

	set("exits", ([
		"east" : "/d/xiangyang/southjie2",
	]));
	set("coor/x", -300);
	set("coor/y", -110);
	set("coor/z", 0);
	setup();
	replace_program(ROOM);
}
