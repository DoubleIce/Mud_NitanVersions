// Room: /d/suzhou/zhenniang.c
// Date: May 31, 98  Java

inherit ROOM;

void create()
{
	set("short", "真娘墓");
        set("long", @LONG
在试剑石北面就是古真娘墓，真娘也称贞娘，因安史之乱流落江
南，受骗流落堕入青楼。贞娘为守贞操，自尽抗之。后人筑亭其上，
墓前石刻『香魂』两字，墓上遍栽花卉。唐代白居易等诗人墨客纷纷
为之题诗，褒赞真娘之贞烈。
LONG );
	set("outdoors", "suzhou");
	set("no_clean_up", 0);
	set("exits", ([
		"north"     : "/d/suzhou/sunwuting",
		"southwest" : "/d/suzhou/shijianshi",
	]));
	set("coor/x", 200);
	set("coor/y", -170);
	set("coor/z", 10);
	setup();
	replace_program(ROOM);
}

