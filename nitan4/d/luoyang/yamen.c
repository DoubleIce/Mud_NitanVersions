// Room: /u/a/agah/yamen.c

inherit ROOM;

void create()
{
	set("short", "衙门正厅");
        set("long", @LONG
堂上东西有两根楹住，挂着一幅对联，但是你无心细看。正墙上
悬挂一个横匾，上书『正大光明』四个金光闪闪的大字。知府正坐在
文案后批阅文书，师爷随侍在后，一帮衙役正分立两旁，在此有什么
冤情你可以直接向知府大人诉说。
LONG );
	set("no_clean_up", 0);
	set("exits", ([ /* sizeof() == 4 */
  "east" : __DIR__"neizhai",
  "south" : __DIR__"sting",
  "west" : __DIR__"yamendoor",
  "north" : __DIR__"bting",
]));

	set("coor/x", -150);
	set("coor/y", 20);
	set("coor/z", 10);
	setup();
	replace_program(ROOM);
}
