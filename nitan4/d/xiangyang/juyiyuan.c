// Room: /d/xiangyang/juyiyuan.c
// Date: Jan. 8 1999 by Winder

inherit ROOM;

void create()
{
	set("short", "大院");
        set("long", @LONG
这里是襄阳安抚使按照郭靖、黄蓉的意思建的用来安置各地前来
效力的义士的地方。南面是一条长长的通廊，东西两边是练武场。
LONG );
        set("outdoors", "xiangyang");
	set("no_clean_up", 0);

	set("exits", ([
		"east"  : "/d/xiangyang/juyilianwu1",
		"west"  : "/d/xiangyang/juyilianwu2",
		"south" : "/d/xiangyang/juyilang",
		"north" : "/d/xiangyang/westjie2",
	]));
	set("objects", ([
		"/d/xiangyang/npc/zhuziliu" : 1,
	]));
	set("coor/x", -320);
	set("coor/y", -90);
	set("coor/z", 0);
	setup();
	replace_program(ROOM);
}

