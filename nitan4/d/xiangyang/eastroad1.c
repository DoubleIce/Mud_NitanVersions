// Room: /d/xiangyang/eastroad1.c
// Date: Jan. 8 1999 by Winder

inherit ROOM;

void create()
{
	set("short", "东内大街");
        set("long", @LONG
这是一条青石铺就的大街。西面是一堵盖着红色琉璃瓦的高墙，
里面是襄阳守城大将王坚的府邸大院。东面是是一座镖局，北面是用
青石铺的大街道。南面是一个大的十字街道，只见人来人往，非常热
闹。
LONG );
        set("outdoors", "xiangyang");

	set("no_clean_up", 0);
	set("exits", ([
		"east"  : "/d/xiangyang/biaoju",
		"south" : "/d/xiangyang/eastjie2",
		"north" : "/d/xiangyang/eastroad2",
	]));
	set("coor/x", -270);
	set("coor/y", -80);
	set("coor/z", 0);
	setup();
	replace_program(ROOM);
}

