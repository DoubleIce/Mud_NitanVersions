inherit ROOM;

void create()
{
	set("short", "仙霞岭");
        set("long", @LONG
这里就是闽浙分水的仙霞岭。向阳的坡面郁郁葱葱，长满了长长
的马尾松。沿途的山路十分难行，来往的口音也渐渐带有闽音，越来
越难以辩识了。
LONG );
	set("exits", ([
                "northdown" : "/d/quanzhou/qzroad4",
                "south"     : __DIR__"erbapu",
	]));
        set("objects", ([
                "/clone/quarry/tu" : 2,
	]));
	set("outdoors", "fuzhou");
	set("coor/x", 80);
	set("coor/y", -50);
	set("coor/z", 10);
	setup();
	replace_program(ROOM);
}

