// Create by lonely@NT
#include <ansi.h>
inherit ROOM;

void create()
{
        set("short", "石壁"NOR);
        set("long", @LONG
这里快到「大宋」军营驻扎地了，远远地可以看见大营内飞扬的
尘土，不时有几匹快马飞奔进出，你正欲再看，忽然嗖地一枚冷箭从
你头上飞过，还是赶快离开的好。
LONG );

        set("no_fly", "1");
        set("exits", ([ /* sizeof() == 5 */   
               "south" :   __DIR__"shance",
               "north" :   __DIR__"luanshi8",
        ]));    

        set("objects", ([

        ]));
    
        setup();
        replace_program(ROOM);
}

