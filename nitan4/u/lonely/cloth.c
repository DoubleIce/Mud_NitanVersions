#include <armor.h>
inherit "/u/lonely/armor1";

void create()
{
        set_name("布衣", ({ "cloth" }));
        set("long", "这是一件非常普通的粗糙布衣。\n"); 
        set_weight(3000);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("unit", "件");
                set("material", "cloth");
                set("armor_prop/armor", 1);
        }
        setup();
}

