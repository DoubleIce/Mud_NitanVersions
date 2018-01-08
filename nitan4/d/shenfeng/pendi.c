inherit ROOM;

void create()
{
	set("short", "盆地");
        set("long", @LONG
这地方是个盆地，四周高山拱卫，以致风雨不侵，千百年之物仍
能如此完好，实是罕见罕闻，沿路只见遍地白骨，刀枪剑戟，到处乱
丢。城中道路也是如迷宫，令人眼花缭乱。
LONG );
        set("outdoors", "gaochang");

	set("exits", ([
		"east" : __DIR__"feixu2",
		"north" : __DIR__"shanjiao",
	]));

	setup();
	replace_program(ROOM);
}
