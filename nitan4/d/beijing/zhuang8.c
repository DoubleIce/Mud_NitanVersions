#include <ansi.h>

inherit ROOM;

void create()
{
    set("short", "长廊");
        set("long", @LONG
这是条长长的走廊，四处黑沉沉的。
LONG );
    set("exits", ([
	"north" : "/d/beijing/zhuang9",
	"south" : "/d/beijing/zhuang5",
    ]));
    set("objects", ([
	"/d/shenlong/npc/dizi": 1,
    ]));
    set("outdoors", "beijing");
    setup();
    replace_program(ROOM); 
}
