// Room: /d/suzhou/leitai.c
// Date: May 31, 98  Java

inherit ROOM;

void create()
{
	set("short", "擂台前广场");
        set("long", @LONG
这里是苏州擂台前面的一个大型广场，有许多人正在擂台上比武，
到处是人山人海，如果你也想试试身手，那么就请跳上擂台比试比试
吧。
LONG );
	set("outdoors", "suzhou");
	set("no_clean_up", 0);
	set("exits", ([
		"east"  : "/d/suzhou/hutong1",
	]));
	set("coor/x", 200);
	set("coor/y", -200);
	set("coor/z", 0);
	setup();
	replace_program(ROOM);
}

