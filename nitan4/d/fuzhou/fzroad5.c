// Room: /d/fuzhou/fzroad5.c
// Date: May 12, 98  Java

inherit ROOM;

void create()
{
	set("short", "闽赣古道");
        set("long", @LONG
福建境内数不尽的山坎相连。密林幽谷相继，终日不见天光。山
中毒虫猛兽出没无常，行路艰辛。路边有一年轻汉子倚在树上冷眼看
着你。
LONG );
	set("exits", ([
		"westup"    : __DIR__"fzroad6",
		"northeast" : __DIR__"fzroad4",
	]));
        set("objects", ([
		"/d/qingcheng/npc/fang" : 1,
	]));
	set("outdoors", "fuzhou");
	set("coor/x", 60);
	set("coor/y", -110);
	set("coor/z", 0);
	setup();
	replace_program(ROOM);
}

