// Room: /d/fuzhou/puxian.c
// Date: May 12 1998 Java

inherit ROOM;

void create()
{
	set("short", "莆仙平原");
        set("long", @LONG
你走在莆仙平原上。这里物产丰饶，人烟稠密，望北就是福州府
城了。往南就进入闽南。
LONG );
	set("exits", ([
		"north" : __DIR__"zhongzhou",
                "south" : "/d/quanzhou/beimen",
	]));
	set("outdoors", "fuzhou");
	set("coor/x", 150);
	set("coor/y", -160);
	set("coor/z", 0);
	setup();
	replace_program(ROOM);
}

