inherit ROOM;

void create()
{
        set("short", "碎石路");
        set("long", @LONG
这是一条由碎石铺成的路，虽然有些颠簸，却很宽阔，南去就是
长江了。不过前面一片乱石，拦住了去路，据说是当年诸葛亮为了阻
止吴兵追赶而设的。
LONG );
	set("objects", ([
		__DIR__"npc/boy" : 1,
		__DIR__"npc/girl" : 1,
	]));
        set("exits", ([
                "north" : __DIR__"nanshilu",
                "south" : "/d/kunming/road1",
        ]));

        set("no_clean_up", 0);
        set("outdoors", "jingzhou");

        set("coor/x", -450);
	set("coor/y", -260);
	set("coor/z", 20);
	setup();
        replace_program(ROOM);
}

