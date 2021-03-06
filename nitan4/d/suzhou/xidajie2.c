// Room: /d/suzhou/xidajie2.c
// Date: May 31, 98  Java

inherit ROOM;

void create()
{
	set("short", "西大街");
        set("long", @LONG
你走在西大街上，感到这里的街面要比别处的干净、整洁。大概
因为靠近衙门、兵营可受保护的缘故，富人们都喜欢住在这里。东边
静悄悄地没有几个行人，西边是西城门通往郊外。南边是玄妙观，北
边是一个书堂。
LONG );
	set("outdoors", "suzhou");
	set("no_clean_up", 0);
	set("exits", ([
		"east"      : "/d/suzhou/xidajie1",
		"west"      : "/d/suzhou/ximen",
		"north"     : "/d/suzhou/shuchang",
		"south"     : "/d/suzhou/xuanmiao",
	]));
	set("coor/x", 180);
	set("coor/y", -210);
	set("coor/z", 0);
	setup();
	replace_program(ROOM);
}

