// Room: /d/xiangyang/westjie1.c
// Date: Jan. 8 1999 by Winder

inherit ROOM;

void create()
{
	set("short", "西大街");
        set("long", @LONG
这是一条宽阔的青石板街道，向东西两头延伸。西边是一个大十
字街口。东面是襄阳的中央广场，北边是人称郭大侠郭靖的府邸大门，
不时地有人从那里进进出出。南面是一家当铺，听说里面常能买到你
所需的东西。
LONG );
        set("outdoors", "xiangyang");
	set("no_clean_up", 0);

	set("exits", ([
		"east"  : "/d/xiangyang/guangchang",
		"west"  : "/d/xiangyang/westjie2",
		"south" : "/d/xiangyang/dangpu",
		"north" : "/d/xiangyang/guofugate",
	]));
	set("objects", ([
		"/d/xiangyang/npc/poorman" : 1,
	]));
	set("coor/x", -300);
	set("coor/y", -90);
	set("coor/z", 0);
	setup();
	replace_program(ROOM);
}

