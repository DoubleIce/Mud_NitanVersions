// Room: /huanghe/shixiazi.c
// Java Sep. 22 1998

#include <room.h>

inherit ROOM;

void create()
{
	set("short", "ʯϿ��");
        set("long", @LONG
ʯϿ������ǰ�Ļƺӹʵ������ڱ���Ǵ��СС�Ķ���ʯ������
�����ɸߵĸ��£�ǧ�����֣�������˵�����µĲ�ɣ��Ҫ�������õ�
�������������𵽷ǳ�Ư�����ǳ������껨ʯ��
LONG );
	set("exits", ([
		"southwest" : __DIR__"tumenzi",
		"northeast" : __DIR__"bingcao",
	]));
	set("objects", ([
		"/d/city/obj/shitou" : 1,
		"/d/hangzhou/obj/eluanshi" :1,
	]));
//	set("no_clean_up", 0);
	set("outdoors", "huanghe");
	set("coor/x", -50);
	set("coor/y", 140);
	set("coor/z", 0);
	setup();
	replace_program(ROOM);
}
