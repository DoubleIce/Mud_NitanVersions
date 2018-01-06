#include <ansi.h>

inherit INLAID;

void create()
{
        set_name(BLU "宝石碎片" NOR, ({ "blu gem1","gem1" }));
        set_weight(20);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("long", BLU "一片蓝色的宝石碎片。\n" NOR);
                set("unit", "片");
                set("value", 80000);
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

