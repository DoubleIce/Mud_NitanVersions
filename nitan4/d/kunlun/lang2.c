inherit ROOM;

void create()
{
	set("short", "长廊");
        set("long", @LONG
这是一条长廊，连接三圣堂和花园，不断看见各种打扮的江湖人
士走过，看过廊外，是一片青色的树林，幽静雅致，只听见不断传来
的鸟鸣声。
LONG );
        set("exits",([
		"southup" : __DIR__"sanshengtang",
		"north" : __DIR__"huayuan1",
	]));

	set("outdoors", "kunlun");
	setup();
	replace_program(ROOM);
}
