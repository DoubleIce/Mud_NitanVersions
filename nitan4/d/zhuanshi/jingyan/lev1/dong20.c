#include <room.h>
#include <ansi.h>
inherit ROOM;

void create()
{
	set("short", CYN"ʯ��"NOR);
        set("long", @LONG
[36m����һ��������ʯ������Χ���Ǽ�Ӳ��ʯ�ڣ������н����ƺ���
��һֱ����ȥ�� [2��37��0m
LONG );
	set("exits", ([
		"north" : __DIR__"dong19",
		"south" : __DIR__"dong10",
                "down" : "/d/jingyan/lev2/dong1"
                	]));
	set("no_clean_up", 0);
	setup();
	replace_program(ROOM);
}
