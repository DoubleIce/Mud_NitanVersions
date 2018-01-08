inherit ROOM;

void create()
{
	set("short", "永徽道");
        set("long", @LONG
站在永徽大街上，你会发现这条街有快慢道之分，街道两旁栽植
松柏，到处是张灯结彩。大街两旁排列着许多店铺。临街店铺里经营
着汴绣、字画、陶瓷、古董、名酒、小吃等，真是热闹非凡。向西就
是洛阳中心广场了，南北两边分别是武器店和盔甲店，同属一个老板
所开。
LONG );
        set("outdoors", "luoyang");
        set("no_clean_up", 0);
        set("exits", ([
  		"east" : __DIR__"eroad2",
  		"north" : __DIR__"armor",
  		"south" : __DIR__"weapon",
  		"west" : __DIR__"center",
	]));
        set("objects", ([
                "/d/beijing/npc/maiyi1" : 1,
                "/d/beijing/npc/kid1" : 2,
        ]));
	set("coor/x", -160);
	set("coor/y", 0);
	set("coor/z", 10);
	setup();
	replace_program(ROOM);
}
