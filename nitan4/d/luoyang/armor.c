inherit ROOM;

void create()
{
	set("short", "盔甲店");
        set("long", @LONG
这家盔甲店和街对面的武器店都是同一个老板开的，之所以把它
们分开，只是为了方便顾客购买自己需要的东西，店内四壁上挂满了
各式个样的盔甲，金制的，银制的，铜制的，铁制的，皮制的，品种
齐全，应有尽有。
LONG );
        set("no_fight", 1);
	set("no_clean_up", 0);
	set("exits", ([
  		"south" : __DIR__"eroad1",
	]));
        set("objects", ([
                __DIR__"npc/zhu" : 1,
        ]));
	set("coor/x", -160);
	set("coor/y", 10);
	set("coor/z", 10);
	setup();
	replace_program(ROOM);
}
