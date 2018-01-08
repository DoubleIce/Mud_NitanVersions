inherit ROOM;

void create()
{
	set("short", "后台");
        set("long", @LONG
这里是戏院的后台，地方不大，除了化妆台，就没有什么了，到
处都堆满了服装和道具，显得很紧凑，人人都紧张的忙碌着，化妆的
化妆，卸妆的卸妆，修道具的修道具，理服装的理服装，大家都在为
前台的表演做着准备。
LONG );
	set("no_clean_up", 0);
	set("exits", ([
  		"west" : __DIR__"xiyuan",
	]));
        set("objects", ([
                "/d/beijing/npc/xizi1" : 2,
        ]));
	set("coor/x", -150);
	set("coor/y", -10);
	set("coor/z", 10);
	setup();
	replace_program(ROOM);
}
