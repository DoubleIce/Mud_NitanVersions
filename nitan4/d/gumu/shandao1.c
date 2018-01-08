inherit ROOM;

void create()
{
        set("short", "山道");
        set("long", @LONG
此段山路是沿着峭壁开凿出来的，特别崎岖难行。有时峭壁边必
须面贴山璧，侧身而过。尤其是当山凤吹来时，更需特别小心，不然
一失足，就要掉进万丈深渊了。往东南是一块广大的空地。往北下通
往后山脚，远远可以望见一个较大的湖。
LONG );
        set("outdoors", "quanzhen");
        set("exits", ([
                "southeast"   : __DIR__"shanlu7",
                "northdown"   : __DIR__"shandao2",
        ]));

        setup();
        replace_program(ROOM);
}
