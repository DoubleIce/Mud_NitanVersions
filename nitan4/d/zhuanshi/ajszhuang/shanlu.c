// shanlu.c copyright by yuchang


inherit ROOM;

void create()
{
        set("short", "山道");
        set("long", @LONG
这是一条笔直的山路向前方延伸，一直隐没于云雾之中，
不知怎么这里的人烟越来越稀少，你不禁暗自嘀咕不会出什
么事吧？你鼓起勇气继续想前走着。
LONG
        );

        set("outdoors", "qianhuigu");

        set("exits", ([ /* sizeof() == 3 */
                "west" : __DIR__"shangu",
                "south" : "/d/zhongzhou/yanlingdong2",
                "east" : __DIR__"kedian",
        ]));

        setup();
       // replace_program(ROOM);
}

