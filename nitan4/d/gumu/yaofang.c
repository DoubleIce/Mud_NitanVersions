// July 31,2000
// Code by April
// yaofang.c

inherit ROOM;

void create()
{
	set("short","药房");

        set("long", @LONG
这是一间药房。屋子一角有个药炉，闻名天下的古墓圣药就在这
里炼制。
LONG );

	set("exits",([ 
		"east" : __DIR__"xiaowu1",
        ]));

	set("objects", ([
                __DIR__"obj/yaolu" : 1,
                __DIR__"npc/baiyi_yaofang" : 1,
        ]));

	setup();
}

