inherit ROOM;

void create()
{
	set("short", "树林");
        set("long", @LONG
树林里光线暗淡，只能听见头顶上传来些鸟儿的啼鸣。偶而从茂
密的叶间透过的一线光伴着落叶在飞舞。朽木腐烂的气味和身後传来
野兽的啸声使人不觉犹豫了前进的脚步。
LONG );
	set("exits", ([
		"west"      : __DIR__"shulin6",
		"southeast" : __DIR__"shulin4",
		"northeast" : __DIR__"tiandi2",
	]));
	set("objects", ([
		"/d/taishan/npc/tangzi" : 1,
	]));
	set("no_clean_up", 0);
	set("outdoors", "huanghe");
	set("coor/x", -50);
	set("coor/y", 50);
	set("coor/z", 0);
	setup();
	replace_program(ROOM);
}

