inherit ROOM;

void create()
{
	set("short", "东厅");
        set("long", @LONG
这里是万俯内的东厅，房间里摆着一张桌子，以及一个书架，书
架上放着很多书籍，墙上挂着几幅字画，这里好像是万门弟子练功的
地方。
LONG );
	set("exits", ([
		"west" : __DIR__"dayuan",		
	]));

	set("coor/x", -460);
	set("coor/y", -180);
	set("coor/z", 10);
	setup();
	replace_program(ROOM);
}

