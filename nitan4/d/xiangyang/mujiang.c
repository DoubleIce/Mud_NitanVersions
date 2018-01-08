// Room: /d/xiangyang/mujiang.c
// Date: Jan. 8 1999 by Winder

inherit ROOM;

void create()
{
	set("short", "木匠铺");
        set("long", @LONG
这是一家简陋的木匠铺，一个中年木匠正蹲在地上钉东西。值此
乱世，木匠们也只好制作些刀枪棍棒什么的以养家糊口。地上和墙角
凌乱地堆放着一些木剑，木刀，木棍什么的，还有几件象锯子，刨子
一类的木匠工具。
LONG );
	set("exits", ([
		"north" : "/d/xiangyang/eastjie3",
	]));
	set("objects", ([
		"/d/xiangyang/npc/mujiang" : 1,
	]));
	set("coor/x", -260);
	set("coor/y", -100);
	set("coor/z", 0);
	setup();
	replace_program(ROOM);
}

