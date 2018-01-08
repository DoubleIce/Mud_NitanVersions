// Room: eastroad3.c
// Date: Feb.14 1998 by Java

inherit ROOM;
void create()
{
	set("short", "东大街");
        set("long", @LONG
你走在东大街上，踩着坚实的青石板地面。向北是一条宽直的大
道。北边可以通往东城门，西南边通向南大街，东南方就是有名的望
江楼了。东边则是大名鼎鼎的侠义盟成都分部。
LONG );
        set("outdoors", "chengdu");
	set("exits", ([
	    "southeast"  : "/d/city3/wangjianglou",
	    "southwest"  : "/d/city3/southroad1",
	    "north"      : "/d/city3/eastroad2",
            "east"      : "/d/city3/xym_cdfb",
	]));
//	set("no_clean_up", 0);
	set("coor/x", -410);
	set("coor/y", -190);
	set("coor/z", 0);
	setup();
	replace_program(ROOM);
}
