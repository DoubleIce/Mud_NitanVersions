inherit ROOM;

void create()
{
        set("short", "荒道");
        set("long", @LONG
这里的地上是一种黄褐色，红褐色的石砾镶嵌在细细的黄沙之中，
给人以极其怪异的感觉。这里就是西域与中原的中间地带，再往西就
是边塞。
LONG );
        set("outdoors", "gaochang");
        set("exits", ([
                "west" : __DIR__"guandao2",
                "east" : "/d/lanzhou/road",
        ]));
        setup();
        replace_program(ROOM);
}

