#include <room.h>
inherit ROOM;

void create()
{
	set("short", "永内东街");
        set("long", @LONG
永内东街是一条繁华的大街，也是北京最杂乱的地段。一条宽阔
的青石大道从中穿过，向东西两头延伸。西边是京城里著名的凡陛桥。
LONG );
	set("exits", ([
		"west" : "/d/beijing/yong_2",
                "south" : "/d/beijing/zsh_bjdamen",
	]));

	set("outdoors", "beijing");
	setup();
	replace_program(ROOM);
}

