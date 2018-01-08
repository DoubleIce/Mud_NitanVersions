inherit ROOM;

void create()
{
	set("short", "西城根");
        set("long", @LONG
这里是洛阳内城南墙脚。很是冷清，几乎没有人会来这里，你的
面前除了高大的城墙，满地的尘土和杂草就什么也没有了。但是，忽
然你眼睛一花，有两个黑影从你的面前一闪而过，到底是发生了什么
事情呢？
LONG );
        set("outdoors", "luoyang");
        set("no_clean_up", 0);
        set("exits", ([
  		"southeast" : __DIR__"nantou2",
  		"north" : __DIR__"suishi10",
	]));
        set("objects", ([
                "/d/city/npc/liumang" : 1,
                "/d/beijing/npc/hunhun" : 1,
        ]));
	set("coor/x", -220);
	set("coor/y", -40);
	set("coor/z", 10);
	setup();
	replace_program(ROOM);
}
