// Room: /d/suzhou/yunhematou.c
// Date: May 31, 98  Java

inherit ROOM;

void create()
{
	set("short", "运河码头");
        set("long", @LONG
这里是运河码头。它是朝廷漕运要塞，水陆必经之处。运河中来
往船只满载穿梭，极其繁忙。
LONG );
	set("outdoors", "suzhou");
	set("no_clean_up", 0);
	set("exits", ([
		"southeast" : "/d/suzhou/xidajie1",
	]));
	set("coor/x", 180);
	set("coor/y", -200);
	set("coor/z", 0);
	setup();
	replace_program(ROOM);
}

