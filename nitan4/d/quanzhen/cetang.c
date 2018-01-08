#include <ansi.h>
inherit ROOM;

void create()
{
        set("short", "侧堂");
        set("long", @LONG
这里是大堂旁边的侧厅，也是接待重要客人的地方。厅不大，只
摆放着一张桌子和几把椅子。桌上摆放着一盆青松山石的盆景，墙壁
上挂着一些字画。
LONG );
        set("exits", ([
                "east" : __DIR__"guozhendian",
                "west" : __DIR__"huizhentang",
                "north" : __DIR__"shiweishi",
                "south" : __DIR__"datang2",
        ]));
        set("objects", ([
                CLASS_D("quanzhen") + "/li" : 1,
        ]));

        setup();
        replace_program(ROOM);
}
