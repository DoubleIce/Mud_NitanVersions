inherit ROOM;

void create()
{
        set("short", "小集市");
        set("long", @LONG
这里是兰州城的一个小集市。南边有一座老酒店，不时传来一阵
阵酒香。由于兰州是西北地区的交通要道，不论到西域还是中原都要
经过这里，所以各地的行人来来往往，你不时可以看见一些人带着满
身酒气从身边经过。
LONG );
        set("no_sleep_room",1);
        set("outdoors", "lanzhou");
        set("exits", ([
                "south"  : __DIR__"jioudian",
                "north"  : __DIR__"xidajie1",
        ]));
        set("objects", ([
                "/d/beijing/npc/dipi" : 1,
                "/d/beijing/npc/hunhun" : 1,
        ]));
        set("coor/x", -520);
	set("coor/y", 100);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}
