// white-cloth.c 白色圣衣
#include <armor.h>
#include <ansi.h>
inherit CLOTH;

void create()
{
        set_name(WHT"白色圣衣"NOR, ({ "cloth" }) );
        set_weight(3000);
        if( clonep() )
                set_default_object(__FILE__);
        else {
		set("long","这是一件绣着红色火焰的白色圣衣。\n");
                set("unit", "件");
                set("material", "cloth");
                set("armor_prop/armor", 40);
        }
        setup();
}
