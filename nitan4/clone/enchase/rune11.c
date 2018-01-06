//rune11.c

// Amn 安姆

#include <ansi.h>

inherit INLAID;

int is_rune() { return 1; }
 
void create()
{
        set_name(HIW "符文" NOR, ({ "rune amn", "rune11", "rune"}));
        set_weight(10);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("long", "符文：安姆(AMN)，可以放入凹槽物品。\n");
                set("unit", "个");
                set("enchase/SN", 11);
                set("enchase/type", "all");
                set("enchase/consistence", 100); 
                set("enchase/weapon_prop", ([
                        "eff_qi"   : 200,
                ]));
                set("enchase/armor_prop", ([
                        "eff_qi"   : 100,
                ]));
                set("value", 20000);
        }
        setup();
}

int query_autoload() { return 1; }

