// Room: /d/suzhou/road1.c
// Date: May 31, 98  Java

inherit BUILD_ROOM;

void create()
{
	set("short", "青石官道");
        set("long", @LONG
你走在一条青石大道上，人来人往非常繁忙，不时地有人骑着马
匆匆而过。大道两旁有一些小货摊，似乎是一处集市。南面就是苏州
城了。
LONG );
	set("outdoors", "suzhou");
	set("max_room", 5);
	set("exits", ([
		"south"     : "/d/suzhou/beimen",
		"southwest" : "/d/suzhou/huqiu",
		"northwest" : "/d/guiyun/shanlu2",
	]));
	set("coor/x", 200);
	set("coor/y", -160);
	set("coor/z", 0);
	setup();
}

