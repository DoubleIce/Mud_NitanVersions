inherit ROOM;

void create()
{
        set("short", "文定南街");
        set("long", @LONG
这是中州文定南街，宽敞的街道看的人不竟心情一畅。街道的东
面熙熙攘攘的是一个菜场。西面的一家店面，一听里面的算盘声就知
道是一家不小的钱庄。
LONG );
	set("outdoors", "zhongzhou");

        set("exits", ([
                "east" : __DIR__"canchang",
                "south" : __DIR__"wendingnan2",
                "west" : __DIR__"bank",
                "north" : __DIR__"shizhongxin",
        ]));
        set("objects", ([
                "/d/beijing/npc/liumang" : 1,
        ]));

        set("coor/x", -230);
	set("coor/y", -20);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}

