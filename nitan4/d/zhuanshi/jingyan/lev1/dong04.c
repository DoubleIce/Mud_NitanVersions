#include <room.h>
#include <ansi.h>
inherit ROOM;

void create()
{
	set("short", CYN" Ø∂¥"NOR);
        set("long", @LONG
[36m’‚ «“ª∏ˆ∫⁄∆·∆· Ø∂¥£¨÷‹Œß∂º «º·”≤µƒ Ø±⁄°£ [2£ª37£ª0m
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
