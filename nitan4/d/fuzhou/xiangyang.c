inherit ROOM;

void create()
{
	set("short", "向阳巷");
        set("long", @LONG
这里是福州城西向阳巷。北面有一所破败的宅子。西面有一家杂
货铺，专卖女人家用的东西，男人不可以进去。
LONG );

	set("exits", ([
                "east"  : __DIR__"shiqiao",
                "north" : __DIR__"laozhai",
                "west"  : __DIR__"zahuopu",
	]));
	set("outdoors", "fuzhou");
	set("coor/x", 130);
	set("coor/y", -130);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}
