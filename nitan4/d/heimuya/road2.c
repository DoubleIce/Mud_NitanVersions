// road2.c
// by Xiang

inherit ROOM;

void create()
{
        set("short", "黄土路");
        set("long", @LONG
你走在一条黄土路上。西南是一个小高岗，地势险恶，客旅断绝。
东面隐隐可以看到平定州城。
LONG );
        set("outdoors", "heimuya");
        set("exits", ([
            "southwest" : "/d/heimuya/road1",
            "east" : "/d/heimuya/pingdingzhou",
        ]));
        set("no_clean_up", 0);
        setup();
        replace_program(ROOM);
}
