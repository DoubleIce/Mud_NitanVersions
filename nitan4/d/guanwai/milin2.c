inherit ROOM;

void create()
{
        set("short", "密林");
        set("long", @LONG
这是一片茂密的松林，杂乱的生长在倾斜的山坡上。每棵松树都
有三四抱粗细，高达十几丈。树冠枝多叶密，将天空完全遮住，因此
林内显得有些昏暗。树木之间长着很多灌木杂草使行走很艰难，据说
人参就生长在这些杂草之中。
LONG );
        set("exits", ([
                "westdown" : __DIR__"milin1",
                "southup"  : __DIR__"milin3",
        ]));
        set("resource/quarry", ([
                "/clone/quarry/hu" :  40,
                "/clone/quarry/hu2" :  3,
                "/clone/quarry/lang" :  50,
                "/clone/quarry/xiong" :  50,
                "/clone/quarry/lu" :  50,
                "/clone/quarry/bao" :  30,
                "/clone/quarry/song" :  50,
        ]));
        set("objects", ([
                // "/clone/quarry/laohu2" : 1,
		"/d/guanwai/npc/dongbeihu": 1,
        ]));
        set("outdoors", "guanwai");
        setup();
        replace_program(ROOM);
}
