// skull.c 骷髅头

#include <ansi.h>
inherit INLAID;

void create()
{
        set_name(HIB "骷髅头" NOR, ({ "skull1" }) );
        set_weight(30);
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("long", BLU "一个冒着幽蓝色光芒的骷髅头, 有些裂纹。\n" NOR);
                set("value", 80000);
                set("unit", "个");
                set("no_identify", 1);
        }
        setup();
}
