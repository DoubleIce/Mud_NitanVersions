// hongchungqiao.c
// Date: Nov.1997 by Venus
#include <room.h>
inherit ROOM;
void create()
{
        set("short", "洪春桥");
        set("long", @LONG
从这里可以看到西湖十景之一的双峰插云(scenery)。 大道通向
北边，再向西南是通往灵隐寺的路。
LONG );
        set("exits", ([
            "southwest"     : "/d/hangzhou/road3",
            "north"         : "/d/hangzhou/road4",
        ]));
        set("item_desc", ([
        "scenery" : 
"双峰，南高峰在西湖之西南，北高峰在西湖之西北。南北遥遥相对，
只见宿雨初收，双峰隐现在轻风薄雾之中，或浓或淡，时有时无；雾
层飘移，卷舒断续，变幻无穷。\n",
        ]));
        set("outdoors", "hangzhou");
        set("no_clean_up", 0);
        setup();
        replace_program(ROOM);
}

