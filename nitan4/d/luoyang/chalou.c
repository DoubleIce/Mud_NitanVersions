inherit ROOM;

void create()
{
	set("short", "壶记茶楼");
        set("long", @LONG
你一走进来，就闻到一股茶香沁入心脾，精神为之一爽。几张八
仙桌一字排开，坐满了客人，或高声谈笑，或交头接耳。你要想打听
江湖掌故和谣言，这里是个好所在。后面是休息室，到楼上可以听人
说书。
LONG );
	set("no_clean_up", 0);
	set("exits", ([
  		"east" : __DIR__"sroad2",
  		"up" : __DIR__"chalou2",
  		"west" : __DIR__"rest",
	]));
        set("objects", ([
                "/d/beijing/npc/teahuoji" : 1,
        ]));
	set("coor/x", -180);
	set("coor/y", 10);
	set("coor/z", 10);
	setup();
	replace_program(ROOM);
}
