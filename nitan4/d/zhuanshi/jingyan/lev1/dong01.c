#include <room.h>
#include <ansi.h>
inherit ROOM;

void create()
{
	set("short", CYN"ʯ��"NOR);
        set("long", @LONG
[36m����һ��������ʯ������Χ���Ǽ�Ӳ��ʯ�ڡ� [2��37��0m
LONG );
	set("exits", ([
		"east" : __DIR__"dong"+(random(2)+1),
		"south" : __DIR__"dong"+(random(5)+1),
                "west" : __DIR__"dong"+(random(1)+1),
                "north" : __DIR__"dong"+(random(3)+1),
	]));


	set("no_clean_up", 0);
	setup();
	replace_program(ROOM);
}
