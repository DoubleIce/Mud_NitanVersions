#include <ansi.h>
inherit ITEM;

void create()
{
        set_name(HIM "镶嵌之符" NOR, ({ "enchaseA charm", "charm" }));
        set_weight(3000);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("long", HIR "此符文具有防止镶嵌宝物时候将装备爆裂。\n" NOR);
                set("unit", "张");
                set("value", 500000);
        }
        setup();
}

int query_autoload()
{
        return 1;
}


