// Room: zhulin.c 竹林小径
// By Dumbness, 2003-4-28 21:34

inherit ROOM;
void create()
{
        set("short", "竹林小径");
        set("long", @LONG
这里满地枯黄的落叶，走在上面沙沙的轻响，青青竹林掩映着炊
烟袅袅的农家小院，竹林外隐隐传来集市嘈杂的喧哗声。
LONG );
        set("exits", ([ 
		"northeast" : __DIR__"nongshe",
		"southwest" : __DIR__"shanlu2",
	]));

	set("coor/x", -200);
	set("coor/y", -140);
	set("coor/z", 0);
        set("outdoors", "guiyun"); 
	setup();
}
void init()
{
	add_action("do_go","go");
}

int do_go()
{
	if(random(3))
	{
		this_player()->move(this_object());
		return 1;
	}
}
