#include <room.h>
#include <ansi.h>
inherit ROOM;

void create()
{
	set("short", CYN"ʯ��"NOR);
        set("long", @LONG
[36m����һ��������ʯ������Χ���Ǽ�Ӳ��ʯ�ڣ������н����ƺ���
��һֱ����ȥ�� [36m
LONG );
	set("exits", ([
		"north" : __DIR__"dong21",
		"south" : __DIR__"dong21",
                "down" : "/d/jingyan/diyin"
                	]));
	set("no_clean_up", 0);
	setup();
	replace_program(ROOM);
}
