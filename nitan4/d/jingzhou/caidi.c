inherit ROOM;

void create()
{
	set("short", "菜地");
        set("long", @LONG
你看到一片绿油油的菜地，种满了各种各样的菜，有大头菜、白
菜、空心菜……
LONG );

	set("exits", ([
		"east" : __DIR__"whouyuan",
	]));

	set("coor/x", -480);
	set("coor/y", -170);
	set("coor/z", 10);
	setup();
	replace_program(ROOM);
}

