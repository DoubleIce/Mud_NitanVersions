// Room: /huanghe/huanghe4.c
// Java. Sep 21 1998

#include <room.h>

inherit ROOM;
void create()
{
	set("short", "�ƺӰ���");
        set("long", @LONG
�����ǻƺӰ��ߡ��ƺ����ʵ�����Ѿ���ɳ�����ˡ���ɫ�ĺ�
ˮ�ںӴ��﷭���ţ������ţ�����һ�����޴�����ѡ��ƺ���������
��ܵ�����̩ɽ���赲��ת���򱱡�
LONG );
	set("exits", ([
		"west"      : __DIR__"huanghe3",
		"northeast" : __DIR__"huanghe5",
	]));
	set("no_clean_up", 0);
	set("outdoors", "huanghe");
	set("coor/x", 20);
	set("coor/y", 80);
	set("coor/z", 0);
	setup();
	replace_program(ROOM);
}

