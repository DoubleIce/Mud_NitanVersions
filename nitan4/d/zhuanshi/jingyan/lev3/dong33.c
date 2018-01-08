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
		"north" : __DIR__"dong34",
		"south" : __DIR__"dong27",
                	]));
        set("objects", ([
              __DIR__"npc/lev"+(random(9)+1) : 1,
             __DIR__"npc/lev"+(random(9)+1) : 1,
                ]));
	set("no_clean_up", 0);
	setup();
	replace_program(ROOM);
}
