// Room: /huanghe/caodi1.c
// Java. Sep 21 1998

#include <room.h>

inherit ROOM;
void create()
{
	set("short", "�ݵ�");
        set("long", @LONG
������һ��������Ĳݵأ�����һ����ɫ��̺�����ڵ��ϡ��ݴ�
�п���һЩ��֪����С�����к�ġ��Ƶģ������ϵġ������ϡ���Ҷ
�ϵ�¶�����ž�Ө�Ĺ⡣���������ݳǵı��š�
LONG );
	set("exits", ([
		"east" : "/d/city/beimen",
		"west" : __DIR__"caodi2",
	]));
	set("no_clean_up", 0);
	set("outdoors", "huanghe");
	set("coor/x", -10);
	set("coor/y", 30);
	set("coor/z", 0);
	setup();
	replace_program(ROOM);
}

