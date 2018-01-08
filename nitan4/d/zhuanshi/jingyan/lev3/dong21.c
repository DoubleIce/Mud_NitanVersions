#include <room.h>
#include <ansi.h>
inherit ROOM;

void create()
{
	set("short", CYN"Ê¯¶´"NOR);
        set("long", @LONG
ÕâÊÇÒ»¸öºÚÆáÆáÊ¯¶´£¬ÖÜÎ§¶¼ÊÇ¼áÓ²µÄÊ¯±Ú£¬Ç°ÃæÓĞÌõÍùÉÏµÄ½×
Ìİ¡£[36m
LONG );
	set("exits", ([
		"east" : __DIR__"dong24",
		"west" : __DIR__"dong25",
                "up" : "/d/migong/lev2/dong20",
                	]));
                set("no_clean_up", 0);
	setup();
	replace_program(ROOM);
}
