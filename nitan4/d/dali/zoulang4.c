//Room: /d/dali/zoulang4.c
//Date: June. 29 1998 by Java

inherit ROOM;
void create()
{
	set("short","走廊");
        set("long", @LONG
这是一条长长的走廊，通向各个客人的寝室。到了二楼，毛毡已
经换成纯白，两侧木壁上或刻有花鸟鱼虫，或挂了些许时人的字画，
每隔七八步，就有一处香台，缕缕青烟从铜鹤嘴里游出，闻之精神一
振。
LONG );
	set("exits",([ /* sizeof() == 1 */
	    "enter"    : "/d/dali/guibingshi2",
	    "west"     : "/d/dali/zoulang3",
	]));
	set("no_clean_up", 0);
	setup();
	replace_program(ROOM);
}

