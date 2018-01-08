inherit ROOM;

void create()
{
	set("short", "客厅");
        set("long", @LONG
这里是客厅，里面简单，只有一些椅子和桌子，桌子上摆着写茶
和点心供客人食用。不少的江湖人士不远千里来到这里往往先到这里
歇息片刻，恢复一下。
LONG );
        set("exits",([
		"west" : __DIR__"elang01",
	]));

	set("outdoors", "kunlun");
	setup();
	replace_program(ROOM);
}
