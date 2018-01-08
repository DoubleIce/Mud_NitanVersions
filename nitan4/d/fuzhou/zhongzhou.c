// Room: /d/fuzhou/zhongzhou.c
// Date: May 12 1998 Java

inherit ROOM;

void create()
{
	set("short", "中洲桥");
        set("long", @LONG
中洲桥横越闽江，桥面平整，桥下水花喧闹。中洲为一小岛，尽
是水上人家。
LONG );
	set("exits", ([
		"north" : __DIR__"nanmen",
                "south" : __DIR__"puxian",
	]));
	set("outdoors", "fuzhou");
	set("coor/x", 150);
	set("coor/y", -150);
	set("coor/z", 0);
	setup();
	replace_program(ROOM);
}

