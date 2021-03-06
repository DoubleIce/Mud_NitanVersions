//rune07.c

// Tal 塔爾

#include <ansi.h>

inherit INLAID;

int is_rune() { return 1; }
 
void create()
{
        set_name(HIW "符文" NOR, ({ "rune tal", "rune07", "rune"}));
        set_weight(10);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("long", "符文：塔爾(TAL)，可以放入凹槽物品。\n");
                set("unit", "个");
                set("enchase/SN", 7);
                set("enchase/type", "all");
                set("enchase/consistence", 100); 
                set("enchase/weapon_prop", ([
                        "suck_jing"   : 1000,
                ]));
                set("enchase/armor_prop", ([
                        "jing_damage" : 500,
                ]));
                set("value", 20000);
        }
        setup();
}

int query_autoload() { return 1; }

