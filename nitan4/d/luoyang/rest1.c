inherit ROOM;

void create()
{
        set("short", "男休息室");
        set("long", @LONG
这里是供洗完澡的客人休息的地方，整个房间宽敞整洁，有次序
的放置了许多靠椅，旁边放有热毛巾，自己取用，而且这里还提供茶
水服务。
LONG );
        set("no_clean_up", 0);
        set("exits", ([
                "east" : __DIR__"nanyuchi",
                "west" : __DIR__"yuchi",
        ]));

        set("coor/x", -150);
	set("coor/y", 0);
	set("coor/z", 10);
	setup();
        replace_program(ROOM);
}

