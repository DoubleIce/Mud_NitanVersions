// Room: room64.c
inherit ROOM;
void create()
{
        set("short", "昆仑山");
        set("long", @LONG
四下无声，只有风吹松涛，幽韵天成，仰视苍天，注视群山，令
人不觉怆然而发思古之幽情！往前看，只见一道飞岩，下临绝崖，往
下看，峭壁如刀削，云卷雾涌，深不见底。
LONG );
        set("exits", ([
                "north" : __DIR__"kunlun4",
                "up"   : __DIR__"kunlun13",
        ]));

        set("outdoors", "kunlun");
        setup();
}

void init()
{
        add_action("do_jump","jump");
}
int do_jump(string arg)
{
        object me, room;
        me = this_player();
        
        if (! arg || arg != "down") 
                return notify_fail("你要往哪跳？\n");      
                    
        message_vision("$N犹豫了一下，鼓气勇气，跳了下去。\n", me);

        if ((int)me->query_skill("dodge", 1) < 400) 
        {
                message("vision", me->name() + "急剧向下坠去。看来是凶多吉少了!\n", environment(me), ({me}));
                if (! room = find_object(__DIR__"kunlun8"))
                        room = load_object(__DIR__"kunlun8");
                me->move(room);
                message("vision", "砰！的一个人掉了下来。\n", room, ({me}));
                me->set_temp("die_reason", "掉下绝崖摔死了");
                me->die();
                return 1;
        }

        if (random(100) > 50)
        { 
                if (! room = find_object(__DIR__"kunlun8"))
                        room = load_object(__DIR__"kunlun8");
        } 
        else
        {
                if (! room = find_object(__DIR__"kunlun9"))
                        room = load_object(__DIR__"kunlun9");
        }

        me->move(room);
        message("vision", "砰！的一个人掉了下来。\n", room, ({me}));
        return 1; 
}

