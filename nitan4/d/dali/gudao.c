//Room: /d/dali/gudao.c
//Date: June. 29 1998 by Java

inherit ROOM;
void create()
{
	set("short","古道");
        set("long", @LONG
一条石板古道，两边树木苍翠，山势平缓，南面是一望无际的西
双版纳大森林。大道北面有一片宏伟建筑，一堵里许长的红墙隔开，
越过墙头可见一座高楼耸立，正是大理名胜五华楼。
LONG );
	set("outdoors", "dali");
	set("exits",([ /* sizeof() == 1 */
	    "enter"   : "/d/dali/dating",
	    "west"    : "/d/dali/shanlu6",
	    "east"    : "/d/dali/luyuxi",
	]));
	set("no_clean_up", 0);
	setup();
	replace_program(ROOM);
}

