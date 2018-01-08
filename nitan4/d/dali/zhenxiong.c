//Room: /d/dali/zhenxiong.c
//Date: June. 29 1998 by Java

inherit ROOM;
void create()
{
	set("short","镇雄");
        set("long", @LONG
这里是乌撒部的聚居中心，乌撒是乌蛮族的大部，属乌夷，领有
巴的甸、镇雄、和附近的威宁。这是一座石砌小城，人口不多，居民
散居在镇子附近，镇子上主要是一些商铺和祭祀所。
LONG );
	set("objects", ([
	   "/d/dali/npc/muyangnu": 1,
	   "/d/dali/npc/wshangfan": 1,
	]));
	set("outdoors", "dali");
	set("exits",([ /* sizeof() == 1 */
	    "south"      : "/d/dali/badidian",
	    "north"      : "/d/dali/gelucheng",
	    "northeast"  : "/d/dali/minadian",
	    "east"       : "/d/dali/titian1",
	    "west"       : "/d/dali/wuyiminju3",
	]));
	setup();
	replace_program(ROOM);
}

