// Room: /city/biaojuhy.c
// YZC 1995/12/04 

inherit ROOM;

void create()
{
	set("short", "福威镖局后院");
        set("long", @LONG
镖局后院是平常镖师们打拳练功之所，除了几个木桩石锁外，别
无它物。
LONG );
	set("exits", ([
		"south" : __DIR__"biaojuzt",
	]));
	set("objects", ([
		__DIR__"npc/zheng" : 1,
	]));
	set("outdoors", "fuzhou");
	set("coor/x", 140);
	set("coor/y", -80);
	set("coor/z", 0);
	setup();
	replace_program(ROOM);
}

