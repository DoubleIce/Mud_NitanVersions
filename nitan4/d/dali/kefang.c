//Room: /d/dali/kefang.c
//Date: June. 29 1998 by Java

inherit ROOM;
void create()
{
	set("short","客房");
        set("long", @LONG
这是一间客房，靠墙放了一张梨木大床，上面的被褥尽是苏绣，
工美绝伦。正中放了一张八仙桌，几个奇服南人正在高谈阔论。
LONG );
	set("objects", ([
	   "/d/dali/npc/peicong": 3,
	]));
	set("exits",([ /* sizeof() == 1 */
	    "out"      : "/d/dali/zoulang2",
	]));
	setup();
	replace_program(ROOM);
}

