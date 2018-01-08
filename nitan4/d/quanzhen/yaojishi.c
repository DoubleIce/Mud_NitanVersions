inherit ROOM;

void create()
{
        set("short", "药剂室");
        set("long", @LONG
这里是全真教制药、配药的地方。这间房间本来很大，只是被前
后左右堆放的药柜药箱挤的显得小多了。药柜已经很陈旧了，不过是
用上好的南海沉香木做成的，据说用这种木材做成的柜子用来储藏东
西不会遭虫蛀。
LONG );
        set("sleep_room",1);
        set("exits", ([
                "east" : __DIR__"xianzhentang",
        ]));

        set("objects", ([
                __DIR__"npc/zhangyao" : 1,
        ]));

        setup();
        replace_program(ROOM);
}
