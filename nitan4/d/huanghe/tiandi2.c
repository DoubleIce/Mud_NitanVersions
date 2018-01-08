inherit ROOM;

void create()
{
	set("short", "田地");
        set("long", @LONG
这里林木渐渐稀疏，不远处有些村庄，炊烟袅袅升起。村庄周围
是一块块的田地，田里有一些正在耕作的农人。
LONG );
	set("exits", ([
		"southwest" : __DIR__"shulin5",
		"east"      : __DIR__"tiandi1",
	]));
	set("outdoors", "huanghe");
	set("coor/x", -40);
	set("coor/y", 60);
	set("coor/z", 0);
	setup();
	replace_program(ROOM);
}

