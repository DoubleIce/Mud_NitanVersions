inherit ROOM;

void create()
{
	set("short", "科举试场");
        set("long", @LONG
洛阳的科举试场是天下最热闹的一所考场，每月初一，全国各地
的士子都来此处赶考。院门两边由士兵看守，要想夹带可不行，围墙
上有张新贴的告示。
LONG );
        set("objects", ([
                "/d/kaifeng/npc/zhukao3" : 1,
                "/d/beijing/npc/shusheng1" : 2,
        ]));
        set("outdoors", "luoyang");
	set("no_clean_up", 0);
	set("exits", ([
  		"east" : __DIR__"nroad3",
	]));

	set("coor/x", -180);
	set("coor/y", 30);
	set("coor/z", 10);
	setup();
	replace_program(ROOM);
}
