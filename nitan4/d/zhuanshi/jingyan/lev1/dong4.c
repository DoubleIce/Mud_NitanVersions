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
		"west" : __DIR__"dong5",
		"east" : __DIR__"dong05",
                	]));
	set("no_clean_up", 0);
	setup();
	replace_program(ROOM);
}
