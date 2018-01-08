inherit ROOM;

void create()
{
        set("short", "密室");
        set("long", @LONG
这里是一间密室，四周散布着几条带血的鞭子，还有一些各种各
样的刑具。看来传说果然不虚，这侯员外果真是个鱼肉乡里的恶霸。
LONG );
        set("exits", ([
                "northwest" : __DIR__"fu-midao",
                "up" : __DIR__"fu-woshi",
        ]));
        set("objects", ([
                "/clone/herb/xuejie" : 1,
        ]));
        setup();
        replace_program(ROOM);
}
