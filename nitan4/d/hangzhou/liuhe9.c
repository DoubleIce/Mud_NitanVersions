// liuhe9.c
// Date: Nov.1997 by Java
#include <room.h>
inherit ROOM;
void create()
{
        set("short", "六和塔");
        set("long", @LONG
这里是六和塔的九层。窗(window)外是浓妆淡抹的西子湖，塔中
玲珑八角，青砖砌地，雕栏飞檐间粘连了些许蛛网。
LONG );
        set("exits", ([
            "down"  : "/d/hangzhou/liuhe8",
            "up"    : "/d/hangzhou/liuhea",
        ]));
        set("objects", ([
            "/d/hangzhou/honghua/zhao" :1,
        ]));
        set("item_desc", ([
            "window": "从窗口望出去，钱江东去。近处农田中，有一农夫正荷锄耕耘。\n",
        ]));
        set("no_clean_up", 0);
        setup();
}
int valid_leave(object me, string dir)
{
        if (dir == "up" &&
            objectp(present("zhao banshan", environment(me))))
            return notify_fail("赵半山笑嘻嘻地挡住你的去路：再玩玩才走啦。气得你半死！\n");
        return ::valid_leave(me, dir);
}
