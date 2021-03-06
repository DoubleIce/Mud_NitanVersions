// Room: /d/fuzhou/yanping.c
// Date: May 12, 98  Java

inherit ROOM;

void create()
{
	set("short", "延平府");
        set("long", @LONG
延平府廛市繁华，占溪山之雄，当水陆之会，向为入闽之咽喉。
周遭山势壁立，深湍饶郭，易守难攻，为省城屏障，故关防严密不轻
怠。隆武天子以国姓爷食栗此方，赐封延平郡王。
LONG );
	set("exits", ([
		"northup"   : __DIR__"fzroad3",
		"southeast" : __DIR__"fzroad8",
		"southwest" : __DIR__"fzroad4",
	]));
        set("objects", ([
		"/d/city/npc/wujiang" : 1,
		"/d/city/npc/bing"    : 2,
	]));
	set("outdoors", "fuzhou");
	set("coor/x", 80);
	set("coor/y", -90);
	set("coor/z", 0);
	setup();
	replace_program(ROOM);
}

