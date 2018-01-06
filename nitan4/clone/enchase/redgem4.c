#include <ansi.h>

inherit INLAID;

void create()
{
        set_name(RED "帝之宝石" NOR, ({ "red gem4","gem4" }));
        set_weight(30);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("long", RED "一块闪烁这奇异光芒的红色宝石，"
                    "让人感到一阵阵的心悸。\n" NOR);
                set("unit", "块");
                set("value", 140000);
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
