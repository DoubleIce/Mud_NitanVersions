// Room: /d/suzhou/wanjing.c
// Date: May 31, 98  Java

inherit ROOM;

void create()
{
	set("short", "万景山庄");
        set("long", @LONG
在虎丘山东面就是万景山庄，是一个较大的盆景园，有盆名为『
秦汉遗韵』的圆柏，树龄已逾五百年，被誉为『盆景之王』。还有盆
景为『云蒸霞蔚』的树石盆景和另一盆四百多年的雀梅古桩盆景，都
是盆景艺术的中的珍品。圆内景色优美，颇富园林雅趣。
LONG );
	set("outdoors", "suzhou");
	set("no_clean_up", 0);
	set("exits", ([
		"eastup" : "/d/suzhou/shijianshi",
		"east"   : "/d/suzhou/toumenshan",
		"westup" : "/d/suzhou/hanhanquan",
	]));
        set("objects", ([
		"/d/taishan/npc/dao-ke" : 1,
	]));
	set("coor/x", 180);
	set("coor/y", -180);
	set("coor/z", 0);
	setup();
	replace_program(ROOM);
}

