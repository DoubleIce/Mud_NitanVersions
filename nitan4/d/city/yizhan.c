// Room: yizhan.c
// YZC 1995/12/04 

inherit ROOM;

void create()
{
        set("short", "扬州驿");
        set("long", @LONG
这是专门用于传递官府公文书简的驿站，高大的木门四面敞开，
而且没有任何门槛和防碍的东西。这是为了让这一些传递紧急公文的
驿使直接冲进来换马节约时间。在东面的房间是为百姓传递信函的。
LONG );
    set("objects", ([
        "/d/city/npc/yiguan":1,
    ]));

        set("exits", ([
                "north" : "/d/city/wumiao",
                "east" : "/d/city/youyi",
        ]));

        set("coor/x", -10);
	set("coor/y", 15);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}

