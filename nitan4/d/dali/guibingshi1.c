//Room: /d/dali/guibingshi1.c
//Date: June. 29 1998 by Java

inherit ROOM;
void create()
{
	set("short","贵宾室");
        set("long", @LONG
这是一间贵宾室，这里窗明几亮，用具考究。单是窗边一架紫竹
软榻已是价值不菲。凭窗眺望，隐隐于淡烟之中可见苍山的玉局峰，
只见山势清秀，翠碧欲滴，令人心旷神怡。
LONG );
	set("exits",([ /* sizeof() == 1 */
	    "out"      : "/d/dali/zoulang3",
	]));
	set("no_clean_up", 0);
	setup();
	replace_program(ROOM);
}

