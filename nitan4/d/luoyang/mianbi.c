inherit ROOM;

void create()
{
	set("short", "面壁室");
        set("long", @LONG
这间屋子是用来惩罚那些先生上课时不认真听讲的孩子的，屋子
又黑又小，而且很闷热，没有任何东西，除了站着不能摆任何姿势，
看样子到这里来受罚的小孩子可要好好吃吃苦头了。
LONG );
	set("no_clean_up", 0);
	set("exits", ([
  		"south" : __DIR__"sishu",
	]));
        set("objects", ([
        ]));
	set("coor/x", -150);
	set("coor/y", 20);
	set("coor/z", 10);
	setup();
	replace_program(ROOM);
}
