inherit ROOM;

void create()
{
  	set ("short", "杂货铺");
        set("long", @LONG
这里是中州城西的一家杂货铺，虽然店内的东西不少，可因为地
处的比较偏僻，所以生意也是冷冷清清。
LONG );

  	set("exits", ([  
    		"south" : __DIR__"yanling1",
 
	]));
        set("objects" , ([
                __DIR__"npc/zhaolaoban" : 1,
        ]));
        set("coor/x", -250);
	set("coor/y", 0);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}
