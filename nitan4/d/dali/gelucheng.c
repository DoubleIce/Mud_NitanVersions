//Room: /d/dali/gelucheng.c
//Date: June. 29 1998 by Java

inherit ROOM;
void create()
{
	set("short","葛鲁城");
        set("long", @LONG
此城是乌蛮族屈部的治府，屈部领葛鲁、昌州、德昌，面积颇大。
附近多山地丛林，居民多狩猎为生，河谷内低地也多草皮，适合放牧
牛羊。此去北和西皆入深山，东边平原上另有村镇。
LONG );
	set("objects", ([
	   "/d/dali/npc/shanyang": 2,
	   "/d/dali/npc/muyangren": 1,
	]));
	set("outdoors", "dali");
	set("exits",([ /* sizeof() == 1 */
	    "northup"    : "/d/dali/shanlin",
	    "south"      : "/d/dali/zhenxiong",
	    "east"       : "/d/dali/minadian",
	]));
	set("no_clean_up", 0);
	setup();
	replace_program(ROOM);
}

