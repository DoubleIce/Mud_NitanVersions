// Room: /d/suzhou/shijianshi.c
// Date: May 31, 98  Java

inherit ROOM;

void create()
{
	set("short", "试剑石");
        set("long", @LONG
在山道东侧是试剑石，呈椭圆形，正中有条深而齐裂的裂缝，相
传吴王得『干将』，『莫邪』剑后，为试其锋利，将石劈开。石旁刻
着元代顾瑛的诗句『剑试一痕秋，崖倾水断流，如何百年后，不斩赵
高头？』的诗句。
LONG );
	set("outdoors", "suzhou");
	set("no_clean_up", 0);
	set("exits", ([
		"northeast" : "/d/suzhou/zhenniang",
		"south"     : "/d/suzhou/qianrenshi",
		"north"     : "/d/suzhou/zhenshi",
		"westdown"  : "/d/suzhou/wanjing",
	]));
	set("objects", ([
		"/d/taishan/npc/jian-ke" : 1,
	]));
	set("coor/x", 190);
	set("coor/y", -180);
	set("coor/z", 10);
	setup();
	replace_program(ROOM);
}

