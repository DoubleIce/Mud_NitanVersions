inherit ROOM;

void create()
{
        set("short", "重阳宫大门");
        set("long", @LONG
你已走到了终南山半山腰，前面就是全真教的总部重阳宫了。殿
宇依山而筑，高低错落有致。但见周围古木森森，翠竹成林，景色清
幽。前方黄墙碧瓦，飞檐翘檩，正中一道三丈来高的朱红杉木包铜大
门(door)。上方一块大匾，龙飞凤舞地书着『重阳宫』三个大字。南
下是广场。
LONG );
        set("outdoors", "quanzhen");
        set("exits", ([
                "southdown"   : __DIR__"daxiaochang",
        ]));

        setup();
        replace_program(ROOM);
}
