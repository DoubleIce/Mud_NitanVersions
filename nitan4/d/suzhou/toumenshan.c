// Room: /d/suzhou/toumenshan.c
// Date: May 31, 98  Java

inherit ROOM;

void create()
{
	set("short", "头门山");
        set("long", @LONG
头山门在虎丘山的南面，形似虎头。隔河照墙上书着『海涌流辉
』四个大字，以示虎丘与大海的渊源关系。
LONG );
	set("outdoors", "suzhou");
//	set("no_clean_up", 0);
	set("exits", ([
		"north" : "/d/suzhou/huqiu",
		"west"  : "/d/suzhou/wanjing",
	]));
        set("objects", ([
		"/d/taishan/npc/jian-ke" : 1,
	]));
	set("coor/x", 190);
	set("coor/y", -180);
	set("coor/z", 0);
	setup();
	replace_program(ROOM);
}

