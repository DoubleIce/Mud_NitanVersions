inherit ROOM;

void create()
{
	set("short", "望星楼四层");
        set("long", @LONG
这里是雅座，文人学士经常在这里吟诗作画，富商土豪也在这里
边吃喝边作交易。这里也是城里举办喜宴的最佳场所。你站在楼上眺
望，只觉得心旷神怡。东面是一池湖水，碧波荡漾，北面则是崇山峻
岭，气势雄浑，巍峨壮观。
LONG );

	set("no_clean_up", 0);
	set("exits", ([
  		"down" : __DIR__"zuixianlou3",
	]));
        set("objects", ([
                __DIR__"npc/libai" : 1,
                "/d/beijing/npc/richman1" : 2,
        ]));
	set("coor/x", -160);
	set("coor/y", 10);
	set("coor/z", 40);
	setup();
	replace_program(ROOM);
}
