inherit ROOM;

void create()
{
	set("short", "闽赣古道");
        set("long", @LONG
进入江西还是不尽的山坎和密林幽谷，终日不见天光。放眼山中
毒虫猛兽出没无常，行路艰辛。一到这里就闻到一股腥风扑鼻而来。
LONG );
	set("exits", ([
		"northwest" : "/d/henshan/hsroad2",
		"eastup"    : __DIR__"fzroad6",
	]));
        set("objects", ([
                // "/clone/quarry/laohu" : 1,
		"/d/fuzhou/npc/huananhu" : 1,
	]));
	set("outdoors", "fuzhou");
	set("coor/x", 40);
	set("coor/y", -110);
	set("coor/z", 0);
	setup();
	replace_program(ROOM);
}

