//ROM

inherit ROOM;

void create()
{
        set("short", "山谷");
        set("long", @LONG
这里是一处山谷，上面种植着草坪。南面是『日月神教』的青龙
堂。向西有一条上山的石道。
LONG );
        set("outdoors", "heimuya");
        set("exits", ([
            "east" : "/d/heimuya/linjxd1",
            "southup" : "/d/heimuya/dating3",
            "west" : "/d/heimuya/shidao1",
        ]));
        set("objects",([
            "/d/heimuya/npc/kid" : 2,
        ]));
//        set("no_clean_up", 0);
        setup();
        replace_program(ROOM);
}
