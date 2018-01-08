inherit ROOM;

void create()
{
        set("short", "茶亭");
        set("long", @LONG
这是一家路边的小茶亭，赶山路的人常在此处歇歇脚。亭子里有
几张桌子和几支条凳。周围是一片树林。
LONG );
        set("exits", ([
                "west" : __DIR__"qzroad4",
        ]));
        set("objects", ([
                CLASS_D("riyue") + "/xiang" : 1,
        ]));
        set("outdoors", "quanzhou");
        set("coor/x", 90);
	set("coor/y", -40);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}

