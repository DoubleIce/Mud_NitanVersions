inherit ROOM;

void create()
{
	set("short", "景云道");
        set("long", @LONG
景云大道位于洛阳城里的南面，是洛阳最繁华地段，青石板铺成
的街面，宽阔而整洁，一到晚上，一派灯红酒绿，尤为热闹。笑声、
歌声、琴声、箫声，汇成一片送入了你的耳朵，你不禁心猿意马，很
想就此停步享受一番。再往南就要到南内城门了，远远望去，可以看
见守城的官兵正在检查排队出城的路人。这里的东边是一间花店，在
里面你可以买到名满天下的洛阳牡丹，西边是鲁氏木器店。
LONG );
        set("outdoors", "luoyang");
        set("no_clean_up", 0);
        set("exits", ([
  		"east" : __DIR__"miaopu",
  		"north" : __DIR__"sroad6",
  		"south" : __DIR__"nandoor",
  		"west" : __DIR__"muqipu",
	]));

	set("coor/x", -170);
	set("coor/y", -40);
	set("coor/z", 10);
	setup();
	replace_program(ROOM);
}
