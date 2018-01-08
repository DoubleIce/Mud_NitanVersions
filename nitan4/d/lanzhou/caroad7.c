inherit ROOM;

void create()
{
        set("short", "青石大道");
        set("long", @LONG
你走在一条青石大道上，人渐渐少起来，只是有时有人骑着马匆
匆而过。远远的你已经可以看到长安城了。
LONG );
        set("outdoors", "lanzhou");

        set("exits", ([
                "north" : __DIR__"caroad6",
                "south" : __DIR__"caroad8",
        ]));

        set("coor/x", -480);
	set("coor/y", 20);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}
