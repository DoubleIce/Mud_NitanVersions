#include <room.h>
#include <ansi.h>
inherit ROOM;

void create()
{
	set("short", CYN"ʯ��"NOR);
        set("long", @LONG
����һ��������ʯ������Χ���Ǽ�Ӳ��ʯ�ڣ������н����ƺ���
��һֱ����ȥ�� [36m
LONG );
	set("exits", ([
		"north" : __DIR__"dong19",
		"south" : __DIR__"dong10",
                "down" : "/d/jingyan/lev3/dong21"
                	]));
	set("no_clean_up", 0);
	setup();
	replace_program(ROOM);
}
