#include <ansi.h>

inherit INLAID;

void create()
{
        set_name(BLU "稀世宝石" NOR, ({ "blu gem3", "gem3" }));
        set_weight(20);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("long", BLU "一颗蓝光闪闪的精美宝石，给人以不同寻常的感觉。\n" NOR);
                set("unit", "块");
                set("value", 120000);
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
