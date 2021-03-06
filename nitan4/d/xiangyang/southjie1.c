// Room: /d/xiangyang/southjie1.c
// Date: Jan. 8 1999 by Winder

inherit ROOM;

void create()
{
	set("short", "南大街");
        set("long", @LONG
这是一条宽阔的青石板街道，向南北两头延伸。南边就是朱雀门，
北面是中央广场，西面是钱庄，东面是襄阳城内的唯一一家学堂。虽
然襄阳战火不断，你仍能听到学堂里传来学生们朗朗地读书声。
LONG );
        set("outdoors", "xiangyang");
	set("no_clean_up", 0);

	set("exits", ([
		"east"  : "/d/xiangyang/xuetang",
		"west"  : "/d/xiangyang/qianzhuang",
		"south" : "/d/xiangyang/southjie2",
		"north" : "/d/xiangyang/guangchang",
	]));
	set("coor/x", -290);
	set("coor/y", -100);
	set("coor/z", 0);
	setup();
	replace_program(ROOM);
}
