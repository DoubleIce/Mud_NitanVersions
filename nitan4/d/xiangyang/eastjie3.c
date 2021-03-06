// Room: /d/xiangyang/eastjie3.c
// Date: Jan. 8 1999 by Winder

inherit ROOM;

void create()
{
	set("short", "东大街");
        set("long", @LONG
这是一条宽阔的青石街道，向东西两头延伸。东面是青龙内门，
南边是木匠铺，锯木声、刨木声声声入耳。北面是襄阳城的东兵营，
隐隐能听见里面传来宋兵的操练声。西边是一个十字街口，只见人来
人往、络绎不绝。
LONG );
        set("outdoors", "xiangyang");
	set("no_clean_up", 0);

	set("exits", ([
		"east"  : "/d/xiangyang/eastgate1",
		"west"  : "/d/xiangyang/eastjie2",
		"south" : "/d/xiangyang/mujiang",
		"north" : "/d/xiangyang/bingying2",
	]));
	set("coor/x", -260);
	set("coor/y", -90);
	set("coor/z", 0);
	setup();
	replace_program(ROOM);
}

