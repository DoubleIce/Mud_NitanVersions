// nl-yuebing.c 
// smallbear 03.9.9

#include <ansi.h>
inherit ITEM;
inherit F_FOOD;

void create()
{
        set_name(HIY"纳凉月饼"NOR, ({"naliang yuebing","yuebing"}));
        set_weight(20);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("long", "一块纳凉月饼，由百合、绿豆、茶水糅进月饼馅精制而成，有清润、美颜之功效。\n"NOR);
                set("unit", "块");
                set("value", 10000);
                set("food_remaining", 5);
                set("food_supply", 20);
        }
}

