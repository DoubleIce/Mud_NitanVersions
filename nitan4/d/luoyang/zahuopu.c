inherit ROOM;

void create()
{
	set("short", "杂货铺");
        set("long", @LONG
不知为什么洛阳虽大，却只有这一间杂货铺。所以每天人来人往，
也挺热闹。这里无论是油盐酱醋，还是大米白面，各种日常用品也是
样样齐全。中间一张柜台，店主人正坐在柜台后面算帐。据说私底下
他也卖一些贵重的东西。
LONG );
	set("no_clean_up", 0);
	set("exits", ([
  		"east" : __DIR__"sroad4",
	]));
        set("objects", ([
                __DIR__"npc/xiao" : 1,
        ]));
	set("coor/x", -180);
	set("coor/y", -10);
	set("coor/z", 10);
	setup();
	replace_program(ROOM);
}
