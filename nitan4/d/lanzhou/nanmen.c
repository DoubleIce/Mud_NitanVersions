inherit ROOM;

string look_gaoshi();

void create()
{
        set("short", "兰州南门");
        set("long", @LONG
这是兰州城的南城门，由于这里的环境干燥，经过几年的风沙侵
蚀显得有些破败。城门正上方勉勉强强可以认出南门两个大字，城墙
上贴着几张通缉告示(gaoshi)。许多来边疆做苦力的罪犯常常经过这
里逃回中原，官兵们戒备森严，动不动就截住行人进行盘问。一条笔
直的青石大道向南北两边延伸。南边是郊外，一些西域来的商人都从
这里出城。许多本地人也赶着牲口从这里经过，到城里去卖掉自己种
的瓜果，再买回生活必需品。北边是城里。
LONG );
        set("outdoors", "lanzhou");
        set("item_desc", ([
                "gaoshi" : (: look_gaoshi :),
        ]));

        set("exits", ([
                "south" : __DIR__"caroad1",
                "north" : __DIR__"nandajie2",
        ]));
        set("objects", ([
                "/d/city/npc/bing" : 4,
                "/d/beijing/npc/ducha" : 1,
                "/clone/npc/walker" : 1,
        ]));
        set("coor/x", -510);
	set("coor/y", 80);
	set("coor/z", 0);
	setup();
}

string look_gaoshi()
{
        return FINGER_D->get_killer() + "\n         兰州知府\n                     耶律巡\n";
}
