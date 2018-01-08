inherit ROOM;

void create()
{
        set("short", "丝绸之路");
        set("long", @LONG
这就是丝绸之路，从古代起这就是中国和西方各国进行经济和文
化交流的一条重要的陆上通道。你走在一条黄土大道上，路的两边种
满了泡桐树，人来人往非常繁忙，不时地有骑着骆驼的西域商人匆匆
而过。许多本地人在大道两旁摆了一些小货摊。这里向南是西北大城
--兰州。
LONG );
        set("outdoors", "lanzhou");
        set("exits", ([
                "west"  : __DIR__"road",
                "south" : __DIR__"beimen",
                "north" : __DIR__"nroad2",
        ]));
        set("objects", ([
                "/d/xingxiu/npc/trader" : 1,
                "/clone/npc/walker" : 1,
        ]));
        set("coor/x", -510);
	set("coor/y", 150);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}

