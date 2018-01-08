inherit ROOM;

void create()
{
	set("short", "英豪酒楼");
        set("long", @LONG
这是中州城最大的酒楼，南来北往的过客都要在此歇歇脚喝壶好
酒。说不准还会交到一两个朋友。大厅挺宽敞，两根大柱子上有几个
斗大的字。要和朋友小聚，楼上还有雅座。据说楼上还有休息室，专
门为了那些有点贪杯的人准备的。
LONG );

        set("valid_startroom", 1);
        set("no_sleep_room",1);
 	set("exits", ([
		"west" : __DIR__"wendingbei1",
		"east" : __DIR__"majiu",
	        "up"   : __DIR__"yinghaoup",
	]));

        set("objects", ([
                __DIR__"npc/xiaoer2" : 1,
        ]));

	set("coor/x", -220);
	set("coor/y", 0);
	set("coor/z", 0);
	setup();
}
