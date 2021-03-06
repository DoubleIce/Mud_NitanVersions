inherit ROOM;

void create()
{
	set("short", "景云道");
        set("long", @LONG
景云大道位于洛阳城里的南面，是洛阳最繁华地段，青石板铺成
的街面，宽阔而整洁，一到晚上，一派灯红酒绿，尤为热闹。笑声、
歌声、琴声、箫声，汇成一片送入了你的耳朵，你不禁心猿意马，很
想就此停步享受一番。走到这里，你突然感到一股强烈的胭脂花粉味
从东面传来，原来那里就是洛阳名楼-春月楼，西边是一间打铁铺，整
天到晚叮叮咚咚响个不停。
LONG );
        set("outdoors", "luoyang");
        set("no_clean_up", 0);
        set("exits", ([
  		"east" : __DIR__"jiyuan",
  		"south" : __DIR__"sroad6",
  		"west" : __DIR__"datie",
  		"north" : __DIR__"sroad4",
	]));
        set("objects", ([
                "/d/beijing/npc/piaoke" : 1,
        ]));
	set("coor/x", -170);
	set("coor/y", -20);
	set("coor/z", 10);
	setup();
	replace_program(ROOM);
}
