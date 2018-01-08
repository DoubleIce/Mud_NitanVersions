// Room: /d/xiangyang/westjie2.c
// Date: Jan. 8 1999 by Winder

inherit ROOM;

void create()
{
	set("short", "西大街");
        set("long", @LONG
这儿是很大的十字街口，北边是西内大街，南面是一座彩楼，楼
前高高的挂着一方大匾，上面用正楷写着『聚义馆』，落款『朱子柳
』。东边通向中央广场，西面可达白虎门。
LONG );
        set("outdoors", "xiangyang");
	set("no_clean_up", 0);

	set("exits", ([
		"east"  : "/d/xiangyang/westjie1",
		"west"  : "/d/xiangyang/westjie3",
		"south" : "/d/xiangyang/juyiyuan",
		"north" : "/d/xiangyang/westroad1",
	]));
	set("objects", ([
		"/d/xiangyang/npc/wusantong" : 1,
	]));
	set("coor/x", -320);
	set("coor/y", -80);
	set("coor/z", 0);
	setup();
	replace_program(ROOM);
}

