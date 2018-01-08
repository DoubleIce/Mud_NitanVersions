inherit ROOM;

void create()
{
        set("short", "青石大道");
        set("long", @LONG
你走在一条青石大道上，四周静悄悄的。西边是一条大道，东边
是好大的一片树林。往南还有一条大道，却掩映在了密密的树林中。
LONG );
        set("outdoors", "wudang");
        set("exits", ([
                "west"    : __DIR__"wdroad5",
                "east"    : "/d/xiaoyao/shulin3",
                "southup" : "/d/henshan/hsroad1",
                "north"   : __DIR__"wdroad3",
        ]));
        set("no_clean_up", 0);
	set("coor/x", -280);
	set("coor/y", -160);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}
