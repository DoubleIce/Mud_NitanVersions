inherit ROOM;

void create()
{
        set("short", "大厅");
        set("long", @LONG
这里是寺内的大厅，几位有道的高僧在高声辩论。看来正在引经
据典，争斗机锋。
LONG );
        set("exits", ([
                "east"  : __DIR__"zoulang1",
                "west"  : __DIR__"zoulang2",
                "north" : __DIR__"cangjing",
                "south" : __DIR__"cangjingge",
                "southwest" : "/d/xueshan/hongdian",
        ]));
        set("objects", ([
                CLASS_D("xueshan")+"/jiumozhi" :1,
        ]));
        setup();
        replace_program(ROOM);
}
