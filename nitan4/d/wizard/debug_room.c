// /d/wizard/guest_room.c

#include <ansi.h>
#include <room.h>
inherit ROOM;

int is_chat_room() { return 1; }

void create()
{
        set("short", HIM "�Խ�ͤ" NOR);
        set("long", @LONG
�����������������Գ���ĵط���
LONG );

	set("exits", ([
                "east": __DIR__"wizard_room",
        ]));


	setup();
}
