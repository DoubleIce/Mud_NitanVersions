inherit ROOM;

void create()
{
	set("short", "福州屏山");
        set("long", @LONG
屏山古称越王山，横亘福州城北，山下华林寺，构法考究。屏山
上俯瞰榕城，历历如画。
LONG );
	set("exits", ([
                "southdown" : __DIR__"beidajie",
	]));
        set("objects", ([
                "/clone/npc/walker" : 1,
        ]));
	set("outdoors", "fuzhou");
	set("coor/x", 150);
	set("coor/y", -90);
	set("coor/z", 10);
	setup();
	replace_program(ROOM);
}

