#include <ansi.h>

inherit INLAID;

void create()
{
        set_name(YEL "宝石" NOR, ({ "yel gem2","gem2" }));
        set_weight(20);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("long", YEL "一颗黄光闪闪的精美宝石，华丽异常。\n" NOR);
                set("unit", "块");
                set("value", 100000);
                set("no_identify", 1);
                set("wear_msg", HIC "$N" HIC "轻轻地把$n" HIC "戴在头上。\n" NOR);
                set("remove_msg", HIC "$N" HIC "轻轻地把$n" HIC "从头上摘了下来。\n" NOR);                   
        }
        setup();
}

int query_autoload()
{
        return 1;
}
