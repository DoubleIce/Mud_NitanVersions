// Room: /d/fuzhou/fzroad9.c
// Date: May 12, 98  Java

inherit ROOM;

void create()
{
	set("short", "闽中大道");
        set("long", @LONG
你走在闽江北岸大道上。福建境内无山不青，无水不翠，山陡林
深少行人，不禁让你惴惴。北面有股青烟冒起，似乎有家野店。
LONG );
	set("exits", ([
		"northwest" : __DIR__"fzroad8",
		"north"     : __DIR__"fzroad10",
		"east"      : __DIR__"fzroad11",
	]));
        set("objects", ([
		"/d/qingcheng/npc/jia" : 1,
	]));
	set("outdoors", "fuzhou");
	set("coor/x", 100);
	set("coor/y", -110);
	set("coor/z", 0);
	setup();
	replace_program(ROOM);
}

