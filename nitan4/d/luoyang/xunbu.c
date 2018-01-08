inherit ROOM;

void create()
{
	set("short", "巡捕房");
        set("long", @LONG
这里是官府发放通缉令的地方，凡是出现什么江洋大盗，大魔头，
杀人犯，都要有这里颁布命令，整个洛阳城里的捕头们才可以展开追
捕行动。巡捕房面积不大，里面放着一个红木大桌用来办公。平时，
普通百姓是不允许进来的。
LONG );
	set("no_clean_up", 0);
	set("exits", ([
  		"north" : __DIR__"laofang",
  		"south" : __DIR__"wroad3",
	]));
        set("objects", ([
                "clone/npc/xunbu" : 2,
        ]));

	set("coor/x", -200);
	set("coor/y", 10);
	set("coor/z", 10);
	setup();
	replace_program(ROOM);
}
