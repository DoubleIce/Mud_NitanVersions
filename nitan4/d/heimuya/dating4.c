//ROM dating
inherit ROOM;
void create()
{
        set("short", "天香堂");
        set("long", @LONG
这是『日月神教』下第四大堂：天香堂的大厅，远远望去郁郁渺
渺，好似不食人间烟火。堂梁上有一块匾(bian)。
LONG );
        set("exits", ([
                "west" : "/d/heimuya/road1",
                "east" : "/d/heimuya/chlang3",
                "southup" : "/d/heimuya/tian1",
        ]));
        set("item_desc", ([
            "bian": "上面写到：天香堂---日月神教圣姑住地。\n",
       	]) );
        set("no_clean_up", 0);
        setup();
        replace_program(ROOM);
}
