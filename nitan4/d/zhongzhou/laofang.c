inherit ROOM;

void create()
{
        set("short", "牢房");
        set("long", @LONG
这是一间阴暗潮湿的牢房，地上几只老鼠莫无旁人在那里找东西
吃。就只有铁门上的一个小窗户透一点光进来。这种地方多呆一刻你
就要发疯。
LONG );
        set("exits", ([
                "west" : __DIR__"xunbu",
        ]));

        set("coor/x", -210);
	set("coor/y", 20);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}

