inherit ROOM;

void create()
{
	set("short", "育婴堂");
        set("long", @LONG
走进育婴堂，你看见到处都是一些小孩子，一位中年妇女正在照
看着这些小孩子，原来这里是替人看孩子的地方，洛阳当地有些夫妇
因为没有时间照看自己的孩子，就把他们送到这里来，有专人看管。
育婴堂里充满了小孩子们的啼哭和喧闹声。
LONG );
	set("no_clean_up", 0);
	set("exits", ([
  		"north" : __DIR__"eroad3",
	]));
        set("objects", ([
                "/d/beijing/npc/girl2" : 1,
                "/d/beijing/npc/kid1" : 1,
                "/d/beijing/npc/girl4" : 1,
                "/d/beijing/npc/boy2" : 1,
        ]));
	set("coor/x", -140);
	set("coor/y", -10);
	set("coor/z", 10);
	setup();
	replace_program(ROOM);
}
