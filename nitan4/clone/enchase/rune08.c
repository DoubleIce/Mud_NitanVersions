//rune08.c

// Ral 拉爾

#include <ansi.h>

inherit INLAID;

int is_rune() { return 1; }
 
void create()
{
        set_name(HIW "符文" NOR, ({ "rune ral", "rune08", "rune"}));
        set_weight(10);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("long", "符文：拉爾(RAL)，可以放入凹槽物品。\n");
                set("unit", "个");
                set("enchase/SN", 8);
                set("enchase/type", "all");
                set("enchase/consistence", 100); 
                set("enchase/weapon_prop", ([
                        "max_jing"      : 2000,
                ]));
                set("enchase/armor_prop", ([
                        "max_jing"      : 1000,
                ]));
                set("value", 20000);
        }
        setup();
}

int query_autoload() { return 1; }

