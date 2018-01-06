//rune04.c

// Nef 那夫

#include <ansi.h>

inherit INLAID;

int is_rune() { return 1; }
 
void create()
{
        set_name(HIW "符文" NOR, ({ "rune nef", "rune04", "rune"}));
        set_weight(10);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("long", "符文：那夫(NEF)，可以放入凹槽物品。\n");
                set("unit", "个");
                set("enchase/SN", 4);
                set("enchase/type", "all");
                set("enchase/consistence", 100); 
                set("enchase/weapon_prop", ([
                        "practice_times"       : 20,
                ]));
                set("enchase/armor_prop", ([
                        "practice_times"       : 10,
                ]));
                set("value", 20000);
        }
        setup();
}

int query_autoload() { return 1; }

