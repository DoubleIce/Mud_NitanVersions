inherit ROOM;

void create()
{
	set("short", "碎石路");
        set("long", @LONG
一条碎石小路，刚下过雨，路面看起来还满干净的．一些乡下人
挑着自己种的蔬菜到城里来卖，人不是很多，吆喝声传出很远。路中
央有一两个乞丐正在行乞，无家可归的人正四处游荡，从这里可以看
出洛阳的另一面。路的两边都是当地的一些民宅。
LONG );
        set("outdoors", "luoyang");
        set("no_clean_up", 0);
        set("exits", ([
  		"north" : __DIR__"wroad7",
  		"south" : __DIR__"suishi11",
	]));

	set("coor/x", -220);
	set("coor/y", -10);
	set("coor/z", 10);
	setup();
	replace_program(ROOM);
}
