// Room: /d/suzhou/beidajie2.c
// Date: May 31, 98  Java

inherit ROOM;

void create()
{
	set("short", "北大街");
        set("long", @LONG
这是一条宽阔的青石街道，向南北两头延伸。北边是北城门通向
城外。南边显得很繁忙。东边是一座两层的楼阁，名为春在楼。西面
是一座庙庵，南面是一条笔直的大街，十分繁华。
LONG );
	set("outdoors", "suzhou");
	set("no_clean_up", 0);
	set("exits", ([
		"east"      : "/d/suzhou/jiudian",
		"west"      : "/d/suzhou/zijinan",
		"north"     : "/d/suzhou/beimen",
		"south"     : "/d/suzhou/beidajie1",
	]));
	set("coor/x", 200);
	set("coor/y", -180);
	set("coor/z", 0);
	setup();
	replace_program(ROOM);
}

