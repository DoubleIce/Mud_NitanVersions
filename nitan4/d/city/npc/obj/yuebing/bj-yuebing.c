// bj-yuebing.c 
// smallbear 03.9.9
#include <ansi.h>
inherit ITEM;
inherit F_FOOD;

void create()
{
        set_name(YEL"保健月饼"NOR, ({"baojian yuebing","yuebing"}));
        set_weight(20);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("long", "一块保健月饼，由人参，药膳糅进月饼馅精制而成，有进补之功效。\n"NOR);
                set("unit", "块");
                set("value", 10000);
                set("food_remaining", 5);
                set("food_supply", 20);
        }
}

