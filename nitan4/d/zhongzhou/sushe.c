inherit ROOM;

void create()
{
        set("short", "演员房间");
        set("long", @LONG
这里是是戏院内演员的休息的地方，好几张大床占了房间的大半，
床上男的女的衣服乱七八糟，看起来他们男的女的就混在一起睡。北
面的墙上有几张名角的画像。
LONG );

        set("exits", ([
                "south" : __DIR__"xiyuan",
        ]));
        set("objects", ([
        	"/d/beijing/npc/kid1" : 2,
        ]));

        set("coor/x", -240);
	set("coor/y", 20);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}
