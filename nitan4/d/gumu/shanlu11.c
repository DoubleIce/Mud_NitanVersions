inherit ROOM;

void create()
{
        set("short", "山路");
        set("long", @LONG
这是一条非常崎岖难行的山路，一路上蜿蜒盘山而上，沿途均是
葱郁的古柏山林，蔚然森秀。在此处可眺望终南山的景色，只见山险
岭峻，山川毓秀。往北上走是金莲阁。往南走是崎岖的山路。
LONG );
        set("outdoors", "quanzhen");
        set("exits", ([
                "northup"   : __DIR__"jinliange",
                "southdown" : __DIR__"shanlu12",
        ]));

        setup();
        replace_program(ROOM);
}
