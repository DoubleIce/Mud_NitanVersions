// Room: /u/a/agah/kefang2.c

inherit ROOM;

void create()
{
	set("short", "南客房");
        set("long", @LONG
这是一间很大的客房，陈设虽然简单，但十分干净整洁。靠墙放
了十几张小木床，不少客人正和衣而卧，满屋子都是呼呼的打酣声。
不时的还有客人进来睡觉，而睡好的人很自觉的悄悄爬起，走出客房。
LONG );
	set("no_clean_up", 0);
	set("exits", ([ /* sizeof() == 1 */
  "north" : __DIR__"kezhan2",
]));

	set("coor/x", -160);
	set("coor/y", 10);
	set("coor/z", 20);
	setup();
	replace_program(ROOM);
}
