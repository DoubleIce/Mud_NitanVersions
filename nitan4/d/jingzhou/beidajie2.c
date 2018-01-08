inherit ROOM;

void create()
{
	set("short", "北大街");
        set("long", @LONG
这是一条宽阔的青石街道，向南北两头延伸。北边是北城门通向
城外。南边显得很繁忙。东边是一家小饭馆，门额上写着『唐氏饭庄
』几个字，阵阵酒肉香酒香让你垂涎欲滴。西边是一间药店。
LONG );
        set("outdoors", "jingzhou");
	set("exits", ([
                "east" : __DIR__"libailou",
		"south" : __DIR__"beidajie1",
                "west" : __DIR__"yaopu",
                "north" : __DIR__"jzbeimen",
	]));
        set("objects", ([
                "/d/beijing/npc/liumang" : 1,
        ]));
	set("coor/x", -460);
	set("coor/y", -180);
	set("coor/z", 10);
	setup();
	replace_program(ROOM);
}

