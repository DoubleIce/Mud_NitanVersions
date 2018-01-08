inherit ROOM;

void create()
{
	set("short", "客厅");
        set("long", @LONG
这里是客厅，里面简单，只有几张床，供疲惫的客人们歇息，屋
子里烤着火，暖烘烘的。
LONG );
        set("exits",([
		"east" : __DIR__"wlang01",
	]));

	set("no_fight",1);
	set("sleep_room",1);
	set("outdoors", "kunlun");
	setup();
	replace_program(ROOM);
}
