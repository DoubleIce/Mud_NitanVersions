inherit ROOM;

void create()
{
        set("short", "丝绸之路");
        set("long", @LONG
这是一条中原和西域之间的商道。东边有一座雄伟的关隘西面则
通往西域。
LONG );

        set("exits", ([
                "east" : __DIR__"jiayuguan",
		"west" : __DIR__"silk2",
        ]));

        set("outdoors", "xiyu");

        setup();
        replace_program(ROOM);
}

