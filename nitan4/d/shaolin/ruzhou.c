inherit ROOM;

void create()
{
	set("short", "汝州城");
        set("long", @LONG
汝州城是本府的大城，立来是兵家必争之地。故州治在此驻扎重
兵，盘查南来北往的行人，并负责翦灭附近山上的草寇。城内一队队
官兵来来去去，一派森严气象。再折向西，就是五岳之一的嵩山。
LONG );
	set("exits", ([
		"west"  : "/d/songshan/taishique",
		"north" : "/d/beijing/road10",
		"south" : __DIR__"yidao3",
	]));
        set("objects", ([
                "/d/city/npc/wujiang" : 1,
                "/d/city/npc/bing" : 3,
                "/clone/npc/walker" : 1,
        ]));
	set("outdoors", "ruzhou");
	set("coor/x", 0);
	set("coor/y", 130);
	set("coor/z", 0);
	setup();
	replace_program(ROOM);
}
