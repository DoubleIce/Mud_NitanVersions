inherit ROOM;

void create()
{
	set("short", "打铁铺");
        set("long", @LONG
这是一家生意兴隆的打铁铺，中心摆着一个火炉，炉火把四周照
得一片通红，你一走进去就感到浑身火热。墙角堆满了已完工和未完
工的菜刀、铁锤、铁棍、匕首、盔甲等物。一位铁匠满头大汗挥舞着
铁锤，专心致志地在打铁。洛阳城里的习武之人都喜欢在这里打造称
手的铁器。墙上有块牌子(paizi)。
LONG );
	set("no_clean_up", 0);
	set("exits", ([
  		"east" : __DIR__"sroad5",
	]));
        set("item_desc",([
                "paizi" : "修补武器防具(repair xxx)。\n",
        ]));
        set("objects", ([
                __DIR__"npc/smith" : 1,
        ]));
	set("coor/x", -180);
	set("coor/y", -20);
	set("coor/z", 10);
	setup();
	replace_program(ROOM);
}
