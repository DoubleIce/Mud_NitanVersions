//Room: /d/dali/atoubu.c
//Date: June. 29 1998 by Java

inherit ROOM;
void create()
{
	set("short","阿头部");
        set("long", @LONG
阿头部是乌杂蛮的部落，和附近的乌蛮一样，也属于乌夷。这里
山高林密，不熟的人轻率进山，很容易迷路丧命。深山对乌夷猎人来
说却是聚宝盆，山中野物皆是美味。
LONG );
	set("objects", ([
	   "/d/dali/npc/lieren": 1,
       "/clone/npc/walker.c":1,
	]));
	set("outdoors", "dali");
	set("exits",([ /* sizeof() == 1 */
	    "north"      : "/d/dali/lushui",
	    "westup"     : "/d/dali/gaolishan1",
	    "southeast"  : "/d/dali/yixibu",
	]));
	setup();
	replace_program(ROOM);
}

