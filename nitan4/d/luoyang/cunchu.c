inherit ROOM;

void create()
{
	set("short", "存储室");
        set("long", @LONG
这里是当铺的存储室，用于存储一些已被典当，但还可能被物主
赎回的东西，当然这只是暂时的，只要一过了可赎回的期限，当铺老
板会毫不犹豫的将其高价出售，要知道商人除了钱是什么也不会认的。
这里阴森黑暗潮湿，而且空气中还充斥着一股霉味。
LONG );
	set("no_clean_up", 0);
	set("exits", ([
  		"up" : __DIR__"dangpu",
	]));

	set("coor/x", -180);
	set("coor/y", 20);
	set("coor/z", 0);
	setup();
	replace_program(ROOM);
}
