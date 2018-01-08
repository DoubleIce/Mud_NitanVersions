//  Room:  /d/city4/hanguguan.c

inherit  ROOM;

void  create  ()
{
	set("short",  "函谷关");
        set("long", @LONG
这里就是古函谷关。它东起崤山，西接潼津，关设于谷中。当年
强秦一隅之地，制关东六国而不敢稍动，最后横扫天下，就是因为它
踞此，进可攻，退可守，乃天下形胜之处。老子西出化胡，也是在此
留下两册道德经，千载以下，后人仍研读不尽。
LONG );
	set("exits",  ([  /*  sizeof()  ==  2  */
		"east"  :  "/d/changan/road1",
		"west"  :  "/d/changan/road2",
		"south" :  "/d/xiangyang/caodi3",
	]));
	set("outdoors", "changan");
	set("coor/x", -300);
	set("coor/y", 0);
	set("coor/z", 0);
	setup();
	replace_program(ROOM);
}
