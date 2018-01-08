// road5.c 小径

inherit ROOM;

void create()
{
        object ob;

	set("short", "小径");
        set("long", @LONG
这是一条蜿蜒的小径，曲曲折折通往山里。路旁有一间小砖房，
烟筒里面时不时冒出一股股黑烟，闻起来有些难受，你一时忍不住想
打两个喷嚏。屋里面传来阵阵的敲打声音，看来这里是给村民们打造
菜刀、犁头的铁匠铺。
LONG );

	set("exits", ([
                "west"  : __DIR__"road4",
                "enter" : __DIR__"xiaowu",
                // "south" : __DIR__"upgrade",
	]));
	set("outdoors", "suzhou");
	setup();
}
