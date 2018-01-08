// road6.c
// by Xiang

inherit ROOM;

void create()
{
        set("short", "黄土路");
        set("long", @LONG
你走在一条黄土路上。陕西的地面，就是看不尽的黄土。向南方
望，远远有高山插云，近处好象有个小小村落。隐隐传来犬吠鸡啼，
给你长途的奔波带来一丝生气。
LONG );
        set("outdoors", "heimuya");
        set("exits", ([
                "southeast" : "/d/village/wexit",
                "north"     : "/d/heimuya/road5",
        ]));
        set("no_clean_up", 0);
        setup();
        replace_program(ROOM);
}
