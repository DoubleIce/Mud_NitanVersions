// shidao1.c

inherit ROOM;

void create()
{
        set("short", "石道");
        set("long", @LONG
一路往北行，中间仅有一道宽约五尺的石道，两边石壁如墙，一
路上都有日月教徒模样的人物在走动，对往来的路人都严密监视。
LONG );
        set("outdoors", "heimuya");
        set("exits", ([
            "east" : "/d/heimuya/guang",
            "north" : "/d/heimuya/shidao2",
        ]));
        set("no_clean_up", 0);
        setup();
        replace_program(ROOM);
}
