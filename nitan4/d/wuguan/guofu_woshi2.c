inherit ROOM;

void create()
{
    	set("short","休息室");
        set("long", @LONG
这里是郭府内的休息室，屋子有点点旧，但是打扫的非常干净，
一排床铺靠墙摆着，东面过去也是一间休息室，不断的有人进来休息
或醒后离去，你悄悄的找个空铺睡了下来。
LONG );
        set("exits", ([
            "west" : __DIR__"guofu_woshi1",
        ]));
        set("no_fight", 1);
        set("sleep_room", 1);
        setup();
}
