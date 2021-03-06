inherit ROOM;

void create()
{
	set("short", "景云道");
        set("long", @LONG
景云大道位于洛阳城里的南面，是洛阳最繁华地段，青石板铺成
的街面，宽阔而整洁，一到晚上，一派灯红酒绿，尤为热闹。笑声、
歌声、琴声、箫声，汇成一片送入了你的耳朵，你不禁心猿意马，很
想就此停步享受一番。东边是一家首饰店，里面摆满了金银珠宝，西
边的水果店，常年有新鲜水果供应。
LONG );
        set("outdoors", "luoyang");
        set("no_clean_up", 0);
        set("exits", ([
  		"east" : __DIR__"shoushi",
  		"south" : __DIR__"sroad7",
  		"west" : __DIR__"shuiguo",
  		"north" : __DIR__"sroad5",
	]));

	set("coor/x", -170);
	set("coor/y", -30);
	set("coor/z", 10);
	setup();
	replace_program(ROOM);
}
