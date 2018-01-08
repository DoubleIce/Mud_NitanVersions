// Room: /u/a/agah/neizhai.c

inherit ROOM;

void create()
{
	set("short", "内宅");
        set("long", @LONG
这里是衙门的内宅，住着知府的家眷。只见宅内布置的富丽堂皇，
珠光宝气，名贵的家具，精致的摆设，大理石铺成的地面映的满堂生
辉。不过外人是不能随便进出的。
LONG );
	set("no_clean_up", 0);
	set("exits", ([ /* sizeof() == 1 */
  "west" : __DIR__"yamen",
]));

	set("coor/x", -140);
	set("coor/y", 20);
	set("coor/z", 10);
	setup();
	replace_program(ROOM);
}
