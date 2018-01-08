inherit ROOM;

void create()
{
	set("short", "永徽道");
        set("long", @LONG
再往西就要到西内城门了，远远望去，可以看见守城的官兵正在
检查排队出城的路人。因为这儿是十字街口，所以非常热闹。小商小
贩们在向行人吆喝着，兜售他们的商品。北边是胡同，许多洛阳城的
老百姓住在里面，南边是一条幽静的碎石小路。
LONG );
        set("outdoors", "luoyang");
        set("no_clean_up", 0);
        set("exits", ([
  		"east" : __DIR__"dongdoor",
  		"north" : __DIR__"hutong",
  		"south" : __DIR__"suishi1",
  		"west" : __DIR__"eroad4",
	]));
        set("objects", ([
                "/d/taishan/npc/jian-ke" : 2,
        ]));
	set("coor/x", -120);
	set("coor/y", 0);
	set("coor/z", 10);
	setup();
	replace_program(ROOM);
}
