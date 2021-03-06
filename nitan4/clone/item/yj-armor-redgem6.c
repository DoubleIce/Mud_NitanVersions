#include <ansi.h>

inherit INLAID;

void create()
{
        set_name(RED "魔之宝石" NOR, ({ "red gem6","gem6" }));
        set_weight(20);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("long", RED "一块闪烁这奇异光芒的红色宝石，"
                    "让人感到一阵阵的心悸。\n" NOR);
                set("unit", "块");
                set("value", 180000);
                set("enchase",  ([ /* sizeof() == 5 */
                        "weapon_prop" : ([ /* sizeof() == 3 */
                                "derive_times"    : 7,
                                "research_times"  : 7,
                                "practice_times"  : 7,
                        ]),
                        "armor_prop" : ([ /* sizeof() == 3 */
                                "research_effect" : 3,
                                "derive_effect"   : 3,
                                "practice_effect" : 3,
                        ]),
                        "level" : 6,
                        "SN" : 1 + random(9),
                        "consistence" : 80 + random(21),
                ])) ;

                set("wear_msg", HIC "$N" HIC "轻轻地把$n" HIC "戴在头上。\n" NOR);
                set("remove_msg", HIC "$N" HIC "轻轻地把$n" HIC "从头上摘了下来。\n" NOR);                   
        }
        setup();
}

