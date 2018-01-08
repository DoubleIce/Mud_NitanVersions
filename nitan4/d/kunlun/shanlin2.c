inherit ROOM;

void create()
{
        set("short", "云杉林");
        set("long", @LONG
这里是一片蜿蜒无尽的翠绿的树林，密密的云杉像撑天的巨伞，
重重叠叠的枝丫，只漏下斑斑点点细碎的日影。林子里十分幽静，连
鸟雀也少飞来，只偶尔能听到远处的几声鸟鸣。
LONG );
	set("exits",([
		"north" : __DIR__"houyuan",
		"east"  : __DIR__"shanlin1",
		"south" : __DIR__"shanlin" + (random(5) + 1),
		"west"  : __DIR__"shanlin" + (random(5) + 1),
	]));
	set("outdoors", "kunlun");
	setup();
	replace_program(ROOM);
}
