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
		"east" : __DIR__"dong"+(random(9)+2),
		"south" : __DIR__"dong"+(random(1)+2),
                "west" : __DIR__"dong"+(random(7)+2),
                "north" : __DIR__"dong"+(random(4)+2),
	]));
          set("objects", ([
         ]));
	set("no_clean_up", 0);
	setup();
	replace_program(ROOM);
}
