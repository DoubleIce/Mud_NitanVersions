// Code of ShenZhou
// Room: didao_s_1.c �ص���
// Zhangchi 7/00

inherit ROOM;
#include "didao.h"

void create()
{
	set("short", "�ص�");
        set("long", @LONG
����һ���ո��ڳɵĵص������������������졣
LONG );
	set("exits", ([
		"north": "/d/mingjiao/didao/didao_s",
]));
	
	set("cost", 1);
	set("valid_dig","south");

	setup();
//	replace_program(ROOM);
}

void init()
{
	int num=get_room("south");
	if (num >= 2)
		set("exits/south","/d/mingjiao/didao/didao_s_2");
	else
		delete("exits/south");

	add_action("do_dig","wa");
	add_action("do_dig","dig");
}
