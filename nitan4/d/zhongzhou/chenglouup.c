inherit ROOM;

void create()
{
  	set ("short", "城楼二层");
        set("long", @LONG
一登上城楼，城外西面的一大片的开阔地尽收眼底，要是在这里
布上弩兵，要是有谁想攻进城来简直比登天还难。
LONG );

	set("outdoors", "zhongzhou");

  	set("exits", ([  
    		"down" : __DIR__"chenglou",
 
	]));

        set("coor/x", -270);
	set("coor/y", -10);
	set("coor/z", 10);
	setup();
        replace_program(ROOM);
}
