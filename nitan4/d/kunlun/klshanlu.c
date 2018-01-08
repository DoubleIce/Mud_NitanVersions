inherit ROOM;

void create()
{
	set("short", "昆仑山麓");
        set("long", @LONG
整个昆仑山脉雪山连绵，冰河垂悬。远望昆仑，有如横卧云彩间
的银色玉龙。每年春天以后，冰雪融化，汇成一股股清澈溪流，流入
长江，黄河。
LONG );
        set("exits",([
	        "northup" : __DIR__"shanmen",
                "east" : __DIR__"shankou",
                "southwest" : "/d/shenfeng/kunlun7",
        ]));
	set("outdoors", "kunlun");
	setup();
	replace_program(ROOM);
}
