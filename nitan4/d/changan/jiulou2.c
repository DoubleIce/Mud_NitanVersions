//Room: jiulou2.c

#include <ansi.h>

inherit ROOM;

void create()
{
        set("short", "望星楼二楼");
        set("long", @LONG
二楼是酒楼的雅座。在这里的客人们都低言慢语，不象楼下的客
人那般狂呼豪饮。二楼卖的酒菜也是望星楼掌厨最拿手的。两旁挂着
长联直贯屋角：[1；31m       君即饮此觞，对酒高歌，人醉楼头，待刘伶同
乐；       余亦醺一梦，临风把盏，云横江上，与王粲销愁。[2；37；0m
LONG );


        set("exits", ([
        	"down" : "/d/changan/jiulou",
        ]));
        set("objects", ([
        	"/d/changan/npc/yang-laoban" : 1,
        ]));

        set("coor/x", -430);
	set("coor/y", 50);
	set("coor/z", 10);
	setup();
        replace_program(ROOM);
}
