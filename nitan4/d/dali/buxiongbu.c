//Room: /d/dali/buxiongbu.c
//Date: June. 29 1998 by Java

inherit ROOM;
void create()
{
	set("short","步雄部");
        set("long", @LONG
这里属江川路，是摆夷的一支--些么徒蛮聚居的地方。此地较偏
远，镇子也不大，南面一片汪洋叫做星云湖，四面山清水秀，桑林密
布。镇北是一片小平原，有些农田。此间桑树多，产丝，乡间民妇多
擅纺丝织麻。
LONG );
	set("objects", ([
	   "/d/dali/npc/bshangfan": 1,
	]));
	set("outdoors", "dali");
	set("exits",([ /* sizeof() == 1 */
	    "west"   : "/d/dali/banshan",
	    "east"   : "/d/dali/yangcanfang",
	    "south"  : "/d/dali/xingyunhu",
	    "north"  : "/d/dali/nongtian5",
	]));
	setup();
	replace_program(ROOM);
}

