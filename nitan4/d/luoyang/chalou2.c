inherit ROOM;

void create()
{
	set("short", "二楼雅座");
        set("long", @LONG
这里相对楼下比较安静，环境更加幽雅，摆设更精致，服务也更
是周到。但收费也会稍微的高那么一点，但更重要的是坐在这里你能
欣赏到说书先生所说的一段段生动有趣，引人入胜的故事，所以一些
上了年纪的老人总是整天捧了个茶壶座在这里。
LONG );
	set("no_clean_up", 0);
	set("exits", ([
  		"down" : __DIR__"chalou",
  		"west" : __DIR__"shuoshu",
	]));
        set("objects", ([
                "/d/beijing/npc/chake" : 1,
        ]));
	set("coor/x", -180);
	set("coor/y", 10);
	set("coor/z", 20);
	setup();
	replace_program(ROOM);
}
