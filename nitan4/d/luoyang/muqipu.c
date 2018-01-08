inherit ROOM;

void create()
{
	set("short", "鲁氏木器铺");
        set("long", @LONG
这是一家专售木器的小店，店面不大，却很整洁。所卖木器不过
是些木刀，木枪之类，鲁老板也整日闲逛，无所事事。但私下听说他
有门祖传手艺，确谁也没见过。
LONG );
	set("no_clean_up", 0);
	set("exits", ([
  		"east" : __DIR__"sroad7",
	]));
        set("objects", ([
                __DIR__"npc/lu" : 1,
        ]));
	set("coor/x", -180);
	set("coor/y", -40);
	set("coor/z", 10);
	setup();
	replace_program(ROOM);
}
