#include <room.h>
#include <ansi.h>
inherit ROOM;

void create()
{
	set("short", CYN"Ê¯¶´"NOR);
        set("long", @LONG
[36mÕâÊÇÒ»¸öºÚÆáÆáÊ¯¶´£¬ÖÜÎ§¶¼ÊÇ¼áÓ²µÄÊ¯±Ú£¬×óÃæÓĞ½×ÌİËÆºõ¿É
ÒÔÒ»Ö±ÍùÏÂÈ¥¡£ [36m
LONG );
	set("exits", ([
		"north" : __DIR__"dong21",
		"south" : __DIR__"dong21",
                "down" : "/d/jingyan/diyin"
                	]));
	set("no_clean_up", 0);
	setup();
	replace_program(ROOM);
}
