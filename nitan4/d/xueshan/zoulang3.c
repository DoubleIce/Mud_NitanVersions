inherit ROOM;

void create()
{
        set("short", "走廊");
        set("long", @LONG
这里是大轮寺内的走廊。这里有点幽暗，天花板上有一些不知道
确切含义的雕刻，墙壁上则是很通俗的佛经故事壁画了。壁上点着几
碗大海灯照明。
LONG );
        set("exits", ([
                "west"  : __DIR__"neidian",
                "south" : __DIR__"zoulang1",
        ]));
        setup();
        replace_program(ROOM);
}
