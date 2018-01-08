// Room: /d/xiangyang/northroad1.c
// Date: Jan. 8 1999 by Winder

inherit ROOM;

void create()
{
	set("short", "北内大街");
        set("long", @LONG
这是一条用青石铺就的大道。只见北面是一条铺面很大的杂货铺，
听说里面能买到许多东西。向东就是丁字街口，西面也是一个大街口，
你好象看到一条大街通向南面。南面是一堵上盖红色琉璃瓦的高墙，
里面是襄阳安抚使吕文德安排给他的布衣客卿、人称郭大侠郭靖的府
邸。
LONG );
        set("outdoors", "xiangyang");

	set("no_clean_up", 0);
	set("exits", ([
		"west"  : "/d/xiangyang/jiekou1",
		"east"  : "/d/xiangyang/dingzi",
		"north" : "/d/xiangyang/xinluofang",
	]));
	set("coor/x", -310);
	set("coor/y", -50);
	set("coor/z", 0);
	setup();
	replace_program(ROOM);
}

