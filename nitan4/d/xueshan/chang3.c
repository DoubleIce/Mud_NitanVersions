inherit ROOM;

void create()
{
        set("short", "武场");
        set("long", @LONG
这里是大轮寺的小练武场，树着好多木桩和沙袋，僧人们日常均
在此刻苦习武。往南走就是大练武场，许多雪山弟子在那里练功。
LONG );
        set("outdoors", "xueshan");

        set("exits", ([
                "north" : __DIR__"houyuan",
                "south" : __DIR__"chang",
        ]));

        setup();
        replace_program(ROOM);
}
