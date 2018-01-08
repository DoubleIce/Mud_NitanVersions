// shimen.c

inherit ROOM;

void create()
{
        set("short", "石门");
        set("long", @LONG
走到一道大石门前，只见两旁刻着两行大字，右首是『文成武德
』，左首是『仁义英明』，横额上刻着『日月光明』四个大红字。
LONG );
        set("outdoors", "heimuya");
        set("objects", ([
            CLASS_D("riyue") + "/zhang2": 1,
        ]));
        set("exits", ([
            "eastdown" : "/d/heimuya/shijie2",
            "westup"   : "/d/heimuya/up1",
        ]));
//        set("no_clean_up", 0);
        setup();
        replace_program(ROOM);
}
