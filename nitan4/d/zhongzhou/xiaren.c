inherit ROOM;

void create()
{
        set("short", "西厢房");
        set("long", @LONG
这是县太爷府里供下人居住的地方。屋内没什么东西，只有一张
桌子和几张竹凳。屋角的盆里放着一大堆的衣服。有几个丫鬟没事正
在绣花。
LONG );
        set("exits", ([
                "east" : __DIR__"huayuan",
                                 
        ]));

        set("objects", ([
	        __DIR__"npc/yahuan" : 2,
        ]));

        set("coor/x", -270);
	set("coor/y", 20);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}
