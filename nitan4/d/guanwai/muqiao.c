// /guanwai/muqiao.c

inherit ROOM;

void create()
{
	set("short", "木桥");
        set("long", @LONG
这是一座年久失修的破木桥，由几根树干捆扎而成。下面的河水
早以结成坚冰。这里本是赫图阿拉城的护城河，现已废弃不用了。河
岸北面是用黄土堆成的城墙，很多处都已坍塌。由此向北就是赫图阿
拉城了。
LONG );
	set("exits", ([
		"north" : __DIR__"nancheng",
		"south" : __DIR__"road8",
	]));
	set("objects", ([
		__DIR__"npc/yuzhenzi" : 1,
	]));
//	set("no_clean_up", 0);
	set("outdoors", "guanwai");
	setup();
	replace_program(ROOM);
}

