inherit ROOM;

void create()
{
        set("short", "高昌迷宫");
        set("long", @LONG
这是条黑沈沈的长甬道，甬道前出现了三条岔道。迷宫之内并无
足迹指引，你不知道要往哪条路走。俯身细看，见左首右首和前方三
条路上都有淡淡的足迹。你似乎迷失了方向，象没头苍蝇般到处乱闯。
LONG );
        set("exits", ([
                "east" : __DIR__"shulin" + (random(10) + 2),
                "south" : __DIR__"kongdi",
                "west" : __DIR__"shulin8",
                "north" : __DIR__"shulin" + (random(10) + 2),
        ]));
        set("outdoors", "gaochang");
        setup();
        replace_program(ROOM);
}
