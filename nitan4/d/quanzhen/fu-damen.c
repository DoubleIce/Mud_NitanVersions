inherit ROOM;

void create()
{
        set("short", "富家大门");
        set("long", @LONG
这里是武功镇上首富--侯员外家的大门，门上挂着一块大横匾，
上面写着侯府两个大字。门内立着一面朱红的影壁，模模糊糊好象题
着一些诗句之类的东西。几个横眉立眼的家丁正挺胸凸肚地站在门口
耀武扬威。
LONG );
        set("outdoors", "wugong");
        set("exits", ([
                "north" : __DIR__"dongjie",
                "south" : __DIR__"fu-xiaoyuan",
        ]));
        set("objects", ([
                __DIR__"npc/jiading" : 3,
        ]));

        setup();
        replace_program(ROOM);
}
