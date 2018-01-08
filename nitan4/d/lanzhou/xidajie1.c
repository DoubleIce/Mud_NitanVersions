inherit ROOM;
void create()
{
        set("short", "西大街");
        set("long", @LONG
你走在一条繁忙的街道上，看着操着南腔北调的人们行色匆匆，
许多人都往东边走去，那里有一个热闹的广场。南边远远的有一家生
意兴隆的小酒店，来自各地的人们进进出出。
LONG );
        set("outdoors", "lanzhou");
        set("exits", ([
                "east" : __DIR__"guangchang",
                "west" : __DIR__"ximen",
                "south" : __DIR__"xiaojisi",
        ]));
        set("coor/x", -520);
	set("coor/y", 110);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}
