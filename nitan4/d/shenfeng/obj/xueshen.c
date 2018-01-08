//xueshen.c
#include <ansi.h>
inherit ITEM;
void init()
{
        add_action("do_eat", "eat");
        add_action("do_eat", "use");
}
void create()
{
        set_name(HIW "雪参" NOR, ({ "xue shen", "shen"}));
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("unit", "棵");
                set("long", "一棵如小儿般，雪白的千年雪参，据说可疗火毒。\n");
                set("value", 2000);
        }
        setup();
}
int do_eat(string arg)
{
        object me = this_player();
        if (!arg|| !this_object()->id(arg))
                return notify_fail("你要吃什么？\n");
        if (me->query_condition("fire_poison")){
                message_vision( "$N吃下一棵千年雪参，顿觉丹田一股寒流上涌，不觉打了个寒战。\n" , me);
                me->apply_condition("fire_poison",0);
                destruct(this_object());
                return 1;
        }
        if ((int)this_player()->query("eff_qi") >= 
            (int)this_player()->query("max_qi"))
                return notify_fail("你现在不需要用千年雪参。\n");

         me->add("qi",30);
         me->add("eff_qi",20);
        message_vision( "$N吃下一棵千年雪参，顿觉丹田一股寒流上涌，不觉打了个寒战，精神觉得好了些。\n" , me);
        destruct(this_object());
        return 1;
}

