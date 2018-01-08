inherit ROOM;

void create()
{
	set("short", "鼓山");
        set("long", @LONG
鼓山以山上有石形如鼓，扣之如擂鼓而得名，非只山势如鼓覆地。
山上苍松滴翠，岩秀谷幽，风景秀丽，四季如春。有晋以来，即为八
闽二绝之一。
LONG );
	set("exits", ([
                "north"    : __DIR__"yongquan",
                "westdown" : __DIR__"shulin",
	]));
	set("objects", ([
                "/clone/quarry/hou" : 1,
	]));
	set("outdoors", "fuzhou");
	set("coor/x", 200);
	set("coor/y", -110);
	set("coor/z", 10);
	setup();
	replace_program(ROOM);
}

