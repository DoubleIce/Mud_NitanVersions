// Room: /d/suzhou/road5.c
// Date: May 31, 98  Java

inherit ROOM;

void create()
{
	set("short", "青石官道");
        set("long", @LONG
你走在一条青石大道上，人来人往非常繁忙，不时地有人骑着马
匆匆而过。北面就是苏州城了。西南边远远望去，波光粼闪，白帆点
缀，便是周遭五百里的太湖了。
LONG );
	set("outdoors", "suzhou");
	set("exits", ([
		"north"     : "/d/suzhou/nanmen",
		"southwest" : "/d/yanziwu/hupan",
                "east"      : "/d/item/road1",
	]));
	set("coor/x", 200);
	set("coor/y", -260);
	set("coor/z", 0);
	setup();
	replace_program(ROOM);
}

