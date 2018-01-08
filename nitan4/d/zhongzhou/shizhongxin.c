inherit ROOM;

void create()
{
	set("short", "市中心");
        set("long", @LONG
这是中州的市中心，两条街道在这里划个大十字。整个中州就数
着两条街道最热闹了。其间三教九流，行行色色的人来来往往。南北
一条宽敞的街道，一看就是刚刚修建好不久，路牌清楚的写着「文定
街」。东西那条街道要陈旧一点，一块路牌上的字已看不太清，依稀
刻着「延陵路」三个字。
LONG );
	set("outdoors", "zhongzhou");
	set("exits", ([
  		"east" : __DIR__"yanlingdong",
  		"south" : __DIR__"wendingnan1",
  		"west" : __DIR__"yanling",
  		"north" : __DIR__"wendingbei1",
	]));
        set("objects", ([
                "/clone/npc/walker" : 1,
        ]));
	set("coor/x", -230);
	set("coor/y", -10);
	set("coor/z", 0);
	setup();
}
