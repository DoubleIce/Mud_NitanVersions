inherit ROOM;

void create()
{
        set("short", "丝绸之路");
        set("long", @LONG
这就是丝绸之路，从古代起这就是中国和西方各国进行经济和文
化交流的一条重要的陆上通道。你走在黄土路上，路的两边种了一些
泡桐树，这里人很少，偶尔有几个骑着骆驼的西域商人向南匆匆走去。
路的两边都是黄土，看上去很荒凉。你听到哗哗的流水声，前面好象
是一条河。
LONG );
        set("outdoors", "lanzhou");
        set("exits", ([
                "southeast" : __DIR__"nroad3",
                "north"     : __DIR__"river-nan",
        ]));
        set("objects", ([
                "/d/beijing/npc/haoke1" : 1,
        ]));
        set("coor/x", -530);
	set("coor/y", 180);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}

