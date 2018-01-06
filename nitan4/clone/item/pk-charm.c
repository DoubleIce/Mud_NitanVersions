#include <ansi.h>
inherit ITEM;

void create()
{
        set_name(HIM "PK报时鸟" NOR, ({ "pk remind", "remind" }));
        set_weight(3000);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("long", HIR "此符文具有提醒玩家对PK对象侦察之功能。\n" NOR);
                set("unit", "张");
                set("value", 500000);
        }
        setup();
}

int query_autoload()
{
        return 1;
}

