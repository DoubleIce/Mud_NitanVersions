// Room: /d/suzhou/beidajie1.c
// Date: May 31, 98  Java

inherit ROOM;

void create()
{
	set("short", "北大街");
        set("long", @LONG
你走在一条繁忙的街道上，看着操着南腔北调的人们行色匆匆，
许多人都往南边走去，那里有一个热闹的亭子。西南面是一家戏园子，
不时传来叫好声，来自各地的人们进进出出。在东面是一个客店。西
面是一个马厩。
LONG );
	set("outdoors", "suzhou");
	set("no_clean_up", 0);
	set("exits", ([
		"east"      : "/d/suzhou/kedian",
		"west"      : "/d/suzhou/majiu",
		"north"     : "/d/suzhou/beidajie2",
		"south"     : "/d/suzhou/canlangting",
		"southwest" : "/d/suzhou/xiyuan",
	]));
	set("coor/x", 200);
	set("coor/y", -190);
	set("coor/z", 0);
	setup();
	replace_program(ROOM);
}

