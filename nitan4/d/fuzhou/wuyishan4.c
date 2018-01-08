// Room: /d/fuzhou/wuyishan4.c
// Date: May 12, 98  Java

inherit ROOM;

void create()
{
	set("short", "天心岩");
        set("long", @LONG
天心岩为武夷名胜，岩下永乐寺为天下著名禅林。山腰『大红袍
』岩茶为天下极品，驰名海内外。
LONG );
	set("exits", ([
		"southeast" : __DIR__"wuyishan5",
	]));
	set("outdoors", "fuzhou");
	set("coor/x", 40);
	set("coor/y", -60);
	set("coor/z", 0);
	setup();
	replace_program(ROOM);
}

