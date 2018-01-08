inherit ROOM;

void create()
{
        set("short", "文庙");
        set("long", @LONG
这里是文庙正殿，内有孔夫子像。历代皇帝都懂得利用儒教思想
来巩固自己的江山社稷，当朝皇帝自然也不例外。不论何人到此，都
毕恭毕敬地上香礼拜。
LONG );
        set("exits", ([
                "west" : __DIR__"nroad3",
        ]));

        set("objects", ([
                "/d/beijing/npc/shusheng1" : 1,
                "/clone/misc/mazedoor" : 1,
        ]));

        set("coor/x", -160);
	set("coor/y", 30);
	set("coor/z", 10);
	setup();
        replace_program(ROOM);
}
