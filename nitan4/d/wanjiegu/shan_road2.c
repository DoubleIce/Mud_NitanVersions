inherit ROOM;

void create()
{
        set("short", "山路");
        set("long", @LONG
这是一条山间小路，两边山坡上张了许多树木，北风吹过发出沙
沙的响声。路上张着许多杂草，看来很少有人走动。
LONG );
        set("outdoors", "wanjiegu");
        set("exits", ([
            "westdown" : __DIR__"shan_road3",
            "eastdown" : __DIR__"shan_road1",
        ]));
        set("objects", ([
            "/d/wanjiegu/npc/haoke" : 2,
            "/d/wanjiegu/npc/bee" : 2,
        ]));
        setup();
        replace_program(ROOM);
}
