#include <room.h>
#include <ansi.h>
inherit ROOM;

void create()
{
	set("short", CYN"Ê¯¶´"NOR);
        set("long", @LONG
ÕâÊÇÒ»¸öºÚÆáÆáÊ¯¶´£¬ÖÜÎ§¶¼ÊÇ¼áÓ²µÄÊ¯±Ú£¬ÓÒÃæÓĞ½×ÌİËÆºõ¿É
ÒÔÒ»Ö±ÍùÏÂÈ¥¡£ [36m
LONG );
	set("exits", ([
		"north" : __DIR__"dong19",
		"south" : __DIR__"dong10",
                "down" : "/d/jingyan/lev3/dong21"
                	]));
	set("no_clean_up", 0);
	setup();
	replace_program(ROOM);
}
