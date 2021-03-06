//rune31.c

// Jah 喬

#include <ansi.h>

inherit INLAID;

int is_rune() { return 1; }
 
void create()
{
        set_name(HIW "符文" NOR, ({ "rune jah", "rune31", "rune"}));
        set_weight(10);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("long", "符文：喬(JAH)，可以放入凹槽物品。\n");
                set("unit", "个");
                set("enchase/SN", 31);
                set("enchase/type", "all");
                set("enchase/consistence", 100); 
                set("enchase/weapon_prop", ([
                        "add_busy"      : 5,              
                ]));
                set("enchase/armor_prop", ([
                        "reduce_busy"   : 1,   
                        "derive_effect" : 20,   
                        "research_effect" : 20,   
                ]));
                set("value", 20000);
        }
        setup();
}

int query_autoload() { return 1; }

