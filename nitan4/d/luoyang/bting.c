// Room: /u/a/agah/bting.c

inherit ROOM;

void create()
{
	set("short", "北厅");
        set("long", @LONG
这里是衙门的北厅，乃是知府的书房。房中有一个亮敞的红木书
桌，书案上凌乱地放着几本发黄的古籍，墙上挂着几副字画，全部出
自名家手笔，一个小书童正在整理着书房中的书籍。
LONG );
	set("no_clean_up", 0);
	set("exits", ([ /* sizeof() == 1 */
  "south" : __DIR__"yamen",
]));

	set("coor/x", -150);
	set("coor/y", 30);
	set("coor/z", 10);
	setup();
	replace_program(ROOM);
}
