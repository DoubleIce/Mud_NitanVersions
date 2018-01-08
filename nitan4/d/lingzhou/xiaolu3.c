inherit ROOM;

void create()
{
	set("short", "林中小路");
        set("long", @LONG
这是陡坡上的一条杂草丛生的羊肠小路，看起来平时没什么人迹，
路边开着不知名的野花，两边松树依然高大挺拔。阳光透下来照的你
身上是斑斑驳驳的影子。
LONG );
	set("exits", ([
		"west" : __DIR__"biangate",
		"east" : __DIR__"xiaolu2",
	]));
	set("outdoors", "lingzhou");
	setup();
	replace_program(ROOM);
}

