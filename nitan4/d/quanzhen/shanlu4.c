inherit ROOM;

void create()
{
        set("short", "山路");
        set("long", @LONG
这里是山路的尽头，南面好象有一片小树林，折而向东就是终南
山的山脚了。
LONG );
        set("outdoors", "wugong");
        set("exits", ([
                "northwest" : __DIR__"shanlu2",
                "eastup" : __DIR__"shanjiao",
                "south" : __DIR__"shulin1",                
        ]));
        setup();
        replace_program(ROOM);
}
