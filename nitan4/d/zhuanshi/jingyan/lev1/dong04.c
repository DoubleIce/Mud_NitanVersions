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
		"east" : __DIR__"dong"+(random(7)+4),
		"south" : __DIR__"dong"+(random(2)+4),
                "west" : __DIR__"dong"+(random(3)+4),
                "north" : __DIR__"dong"+(random(1)+4),
	]));
        set("objects", ([
              "/clone/box/gbox" : random(2),
         ]));
	set("no_clean_up", 0);
	setup();
	replace_program(ROOM);
}
