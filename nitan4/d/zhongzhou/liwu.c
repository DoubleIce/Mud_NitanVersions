inherit ROOM;

void create()
{
        set("short", "漕帮里屋");
        set("long", @LONG
这里是漕帮的里屋，几个流氓恶霸正在赌钱。边上有个小门，是
漕帮为了有事发生的时候的紧急通道。
LONG );
        set("exits", ([
                "out" : __DIR__"eba",
                "south" : __DIR__"hutong2",     
        ]));

        set("coor/x", -220);
	set("coor/y", -30);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}
