#include <room.h>
#include <ansi.h>
inherit ROOM;

void create()
{
	set("short", CYN"Ê¯¶´"NOR);
        set("long", @LONG
[36mÕâÊÇÒ»¸öºÚÆáÆáÊ¯¶´£¬ÖÜÎ§¶¼ÊÇ¼áÓ²µÄÊ¯±Ú¡£ [2£»37£»0m
LONG );
	set("exits", ([
		"north" : __DIR__"dong12",
		"south" : __DIR__"dong15",
                	]));
	set("no_clean_up", 0);
	setup();
	replace_program(ROOM);
}
