// Room: /d/suzhou/road2.c
// Date: May 31, 98  Java

inherit BUILD_ROOM;

void create()
{
	set("short", "青石官道");
        set("long", @LONG
你走在一条青石大道上，人来人往非常繁忙，不时地有人骑着马
匆匆而过。大道两旁有一些小货摊，似乎是一处集市。东面就是苏州
城了。虽然是城外，但是景色宜人，绝对是一个好住处。
LONG );
	set("outdoors", "suzhou");
	set("exits", ([
		"west"  : "/d/suzhou/road3",
		"east"  : "/d/suzhou/ximen",
	]));
        set("max_room", 4);
	set("coor/x", 160);
	set("coor/y", -210);
	set("coor/z", 0);
	setup();
}
