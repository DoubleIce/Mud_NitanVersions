// 上古神器 昆仑镜

#include <ansi.h>

inherit ITEM;

int is_magic_item() { return 1; }

void create()
{
        set_name(HIW "昆仑镜" NOR, ({ "kunlun jing", "kunlun", "jing" }) );
        set_weight(100);
        if (clonep())
                set_default_object(__FILE__);
        else
        {
                set("unit", "面");
                set("long", HIW "这是一面通体银光的镜子，周身泛着眩目的光华，据说拥有穿梭时空的能力。\n"              
                                "可用之来打开(chuansuo)虚空，进入太虚境界。\n" NOR);

        }

        setup();
}

void init()
{
        add_action("do_chuansuo", "chuansuo");       
}

int do_chuansuo(string arg)
{
        object me;
        
        me = this_player();
              
        if (me->is_fighting() || me->is_busy())
                 return notify_fail("你正忙呢！\n");
        
        if (! environment(me)->query("outdoors"))
                 return notify_fail("你得先到户外去。\n");

        message_vision(HIW "\n$N" HIW "举起手中的昆仑镜，刹那间光华万道，$N" HIW "借"
                         "着万道光芒消失在天际 ……\n" NOR, me);                 
                
        me->move("/d/zhuanshi/sky/sky1");
        destruct(this_object());

        return 1;
}

