// shidao1.c

inherit ROOM;

void create()
{
        set("short", "石道");
        set("long", @LONG
一路上日月教教众把守严密，经过三处山道，来到一处水滩之前，
西面有一道石阶通往水滩。
LONG );
        set("outdoors", "heimuya");
        set("exits", ([
            "westdown" : "/d/heimuya/xingxingtan",
            "south" : "/d/heimuya/shidao1",
        ]));
        set("objects", ([
            "/d/heimuya/npc/wangcheng" : 1,
            "/d/heimuya/npc/heiyiren" : 2,
        ]));
        set("no_clean_up", 0);
        setup();
        replace_program(ROOM);
}
