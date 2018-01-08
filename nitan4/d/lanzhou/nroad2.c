inherit ROOM;

void create()
{
        set("short", "丝绸之路");
        set("long", @LONG
这就是丝绸之路，从古代起这就是中国和西方各国进行经济和文
化交流的一条重要的陆上通道。你走在黄土路上，路的两边种满了泡
桐树，这里人不是很多，只有一些有骑着骆驼的西域商人向南匆匆走
过。偶尔有两个本地人在大道旁摆了个小摊。这里向南隐隐约约可以
看到兰州城。
LONG );
        set("outdoors", "lanzhou");

        set("exits", ([
                "south"     : __DIR__"nroad1",
                "northwest" : __DIR__"nroad3",
        ]));
        set("objects", ([
                "/d/beijing/npc/youke" : 2,
        ]));
        set("coor/x", -510);
	set("coor/y", 160);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}
