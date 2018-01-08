// Room: /huanghe/xueguan.c
// Java. Sep 21 1998

#include <room.h>

inherit ROOM;
void create()
{
	set("short", "学馆");
        set("long", @LONG
一间简陋的私塾，四壁皆空，屋子中摆满了学生从自己家里抬来
的方桌、长凳。一张书案放在屋子的一头，案上摆着几本翻开了的〖
三字经〗、〖百家姓〗和一把戒尺。至圣先师孔老夫子的石刻拓片侧
身像贴在书案的後面。
LONG );
	set("exits", ([
		"south"    : __DIR__"gulang",
	]));
	set("objects", ([
		__DIR__"npc/xiucai" : 1,
	]));
//	set("no_clean_up", 0);
	set("coor/x", -60);
	set("coor/y", 100);
	set("coor/z", 0);
	setup();
	replace_program(ROOM);
}

