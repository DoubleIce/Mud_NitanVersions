//rune03.c

// Tir 特爾

#include <ansi.h>

inherit INLAID;

int is_rune() { return 1; }
 
void create()
{
        set_name(HIW "符文" NOR, ({ "rune tir", "rune03", "rune"}));
        set_weight(10);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("long", "符文：特爾(TIR)，可以放入凹槽物品。\n");
                set("unit", "个");
                set("enchase/SN", 3);
                set("enchase/type", "all");
                set("enchase/consistence", 100); 
                set("enchase/weapon_prop", ([
                        "derive_times"  : 20,                 
                ]));
                set("enchase/armor_prop", ([
                        "derive_times"  : 10,       
                ]));
                set("value", 20000);
        }
        setup();
}

int query_autoload() { return 1; }

