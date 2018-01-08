#include <ansi.h>
inherit ROOM;

void create()
{
        set("short", "栈道");
        set("long", @LONG
自古有云：蜀道难，难于上青天，呜呼。无怪大诗人李白如此写。
路到了这里真可谓惊险无比，一边是滔滔的江水，一边是如刀切般的
峭壁，朝西已无路可走，只有峭壁上有一些石窝，可以攀登而上，向
东，却是摇摇晃晃的栈道。 
LONG );
        set("exits", ([
                "east" : __DIR__"shudao6",
                "westup" : __DIR__"shudao8",
        ]));
        set("objects", ([
                "/d/beijing/npc/tangzi" : 1,
        ]));
        set("no_clean_up", 0);
        set("outdoors", "chengdu");
        set("coor/x", -210);
	set("coor/y", -180);
	set("coor/z", -60);
	setup();
        replace_program(ROOM);
}

