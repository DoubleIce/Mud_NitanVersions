// Create by lonely@NT
inherit ROOM;
#include <ansi.h>;
void create()
{
        set("short", HIW"乱石路"NOR);
        set("long", @LONG
这里是雁门关的乱石路，是扼守南北的交通必经之路，历来为兵
家必争之地，由山顶币制而下，只有一条狭窄的羊肠小道，两面则是
堆满乱石，好象暗浮杀机。
LONG );
        set("outdoors", "yanmen");
        set("exits", ([
                "north" :  __DIR__"road",
                "south" :  __DIR__"luanshi2",
        ]));
        set("no_fly",1);
        setup();
        replace_program(ROOM);
}
