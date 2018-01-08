inherit ROOM;

void create()
{
	set("short", "孔庙");
        set("long", @LONG
这里是孔庙正殿，内有孔夫子像。历代皇帝都懂得利用儒教思想
来巩固自己的江山社稷，当朝皇帝自然也不例外。不论何人到此，都
毕恭毕敬地上香礼拜。
LONG );
	set("no_clean_up", 0);
	set("exits", ([
  		"south" : __DIR__"wroad2",
	]));
        set("objects", ([
                "/d/beijing/npc/shusheng2" : 1,
        ]));
	set("coor/x", -190);
	set("coor/y", 10);
	set("coor/z", 10);
	setup();
	replace_program(ROOM);
}
