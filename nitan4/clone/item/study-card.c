// This program is a part of NITAN MudLIB

#include <ansi.h>
inherit ITEM;

void create()
{
        set_name(HIY "高效练功卡" NOR, ({ "study card", "card" }) );
        set_weight(15);  
        if( clonep() ) 
                set_default_object(__FILE__);
        else {
                set("unit", "张");
                set("long", HIY "这是一张双倍经验卡，使用他(use)可以获得2个小时的高效练功。\n" NOR);
                set("value", 1);
        }
}

void init() 
{
        add_action("do_use", "use");
}

int do_use(string arg)
{
        object me;
        
        if( !arg || !id(arg) )
                return notify_fail("你要使用什么？\n");
     
        me = this_player();

        message_vision("$N开始使用双倍练功卡，为自己增加了2个小时的高效练功。\n", me);

        me->add("time_reward/study", 7200);
        destruct(this_object());
        return 1;
}

