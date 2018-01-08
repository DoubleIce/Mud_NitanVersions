#include <ansi.h>
inherit ROOM;

void create()
{
        set("short", "井底");
        set("long", @LONG
这是在一口水井中。光线极暗，什么也看不清， 你模模糊糊的感
觉到旁边都是井壁，井水冰寒刺骨，使你感到受骗的感觉，生出想踢
(ti)人的感觉！
LONG );
        set("exits", ([
                "up" : __DIR__"yuanzi",
        ]));       
        setup();
}

void init()
{
        add_action("do_ti", "ti");
        add_action("do_an", "an");
}

int do_ti(string arg)
{
        object me;
        me = this_player();

        if (!arg || arg != "wall") return notify_fail("你是要踢(wall)吗？\n");
           
        write("你踢了一脚，感觉好象踢中了什么东西,不妨试试按(an wall)看看!\n");
        me->set_temp("tiwall", 1);
        return 1;
}

int do_an(string arg)
{
        object me;
        object room; 
        me = this_player();

        if (! me->query_temp("tiwall", 1)) return 0;

        if( !arg || arg != "wall" ) return notify_fail("你是要按(wall)吗？\n");
  
        message_vision(HIG"\n$N向半尺见方的石块用力按去,发出了「轧轧」声响，\n"
                      "这声响在井底的窄长空间份外触耳。\n"NOR, me); 

        message_vision(HIY"\n井璧缓缓凹陷下去，露出仅可容一人通过的入口。\n"
                      "$N从入口走了进去。\n\n"NOR, me);
            
        me->move(__DIR__"tongdao1");
        message("vision", HBRED"【宝藏传闻】" + me->query("name") + 
                "成功进入了杨公宝库!\n"NOR, users());

        me->delete_temp("tiwall");
        return 1;        
}

