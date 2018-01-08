inherit ROOM;

void create()
{
  	set ("short", "延陵东路");
        set("long", @LONG
从市中心往东走就到了延陵东路，这里中州城内的一条老街。两
边的房屋看上去已经很陈旧了。出门在外到这种地方来转一转也别有
一番滋味。
LONG );

	set("outdoors", "zhongzhou");

  	set("exits", ([  
    		"west" : __DIR__"shizhongxin",
    		"east"  : __DIR__"yanlingdong1",
	]));
       
        set("objects", ([
        	"d/city/npc/liumang" : 1,
        ]));

        set("coor/x", -220);
	set("coor/y", -10);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}
