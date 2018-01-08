inherit ROOM;

void create()
{
	set("short", "石路");
        set("long", @LONG
这是一条铺的十分平整的石板路，路面被打扫得干干净净，南面
过去是个花圆，传来阵阵花香，西面是静修室，东面传来些读书声，
想必那里是书房了。
LONG );
        set("exits",([
		"north" : __DIR__"qianting",
		"south" : __DIR__"huayuan1",
		"west" : __DIR__"jingxiushi",
		"east" : __DIR__"shufang",
	]));

	set("outdoors", "kunlun");
	setup();
	replace_program(ROOM);
}
