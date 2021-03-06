// Room: /d/xiangyang/juyihuayuan.c
// Date: Jan. 8 1999 by Winder

inherit ROOM;

void create()
{
	set("short", "花园");
        set("long", @LONG
这是聚义馆的大花园。园内种着各种各样的花草，清风吹来，你
能闻到股股花香。园内东西两侧各有一排厢房，北面是一湖池水，水
上架着走廊，直通西大街。南面是馆内厨房，东南方向有一间物品房。
LONG );
        set("outdoors", "xiangyang");

	set("exits", ([
		"east"      : "/d/xiangyang/juyifemale",
		"west"      : "/d/xiangyang/juyimale",
		"south"     : "/d/xiangyang/juyichufang",
		"north"     : "/d/xiangyang/juyilang",
		"southeast" : "/d/xiangyang/juyiwupin",
	]));
	set("objects", ([
		"/d/xiangyang/npc/guofu" : 1,
	]));
	set("coor/x", -320);
	set("coor/y", -110);
	set("coor/z", 0);
	setup();
}

int valid_leave(object me, string dir)
{
	if (me->query("gender") != "男性" && dir == "west") 
		return notify_fail("男女有别，请到对面住！\n");

	if (me->query("gender") != "女性" && dir == "east") 
		return notify_fail("男女有别，请到对面住！\n");

	return ::valid_leave(me, dir);
}
