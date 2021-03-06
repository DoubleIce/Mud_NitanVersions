// yuquan.c
// Date: Nov.1997 by Venus
#include <room.h>
inherit ROOM;
void create()
{
        set("short", "玉泉");
        set("long", @LONG
玉泉寺建在玉泉山上，原名清涟寺。走进玉泉寺，只见这里有几
个水池(pond)。朝东就是出寺下山的路。
LONG );
        set("exits", ([
                "eastdown"  : "/d/hangzhou/road5",
                "north"  : "/d/hangzhou/quanbian-xiaojing",
        ]));

        set("item_desc", ([
                "pond": "池旁的石碑刻着“古珍珠泉”，池内偶有小水泡上涌，好象一串珍珠\n",
        ]));

        set("objects" , ([
                "/d/hangzhou/npc/you-ke" : 1,
                "/d/hangzhou/npc/yuenv"  : 1,
        ]));

        set("outdoors", "hangzhou");

        setup();
        replace_program(ROOM);
}
