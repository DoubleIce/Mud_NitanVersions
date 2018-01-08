inherit ROOM;

void create()
{
	set("short", "粮铺");
        set("long", @LONG
这家粮铺是洛阳城附近唯一的一家粮铺，靠近武德道，街道另一
边便是官府。由此可见官府管理甚严。当地居民买米买面都要到这里
来买，所以生意兴隆，客源滚滚。
LONG );
	set("no_clean_up", 0);
	set("exits", ([
  		"east" : __DIR__"nroad2",
	]));
        set("objects", ([
                __DIR__"npc/liangcao" : 1,
        ]));
	set("coor/x", -180);
	set("coor/y", 20);
	set("coor/z", 10);
	setup();
	replace_program(ROOM);
}
