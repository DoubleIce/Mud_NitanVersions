#include <ansi.h>
inherit ITEM;

void create()
{
        set_name(HIM "PK保护符" NOR, ({ "nopk charm", "charm" }));
        set_weight(3000);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("long", HIR "此符文具有保护玩家不被PK之功能。\n" NOR);
                set("unit", "张");
                set("value", 500000);
        }
        setup();
}

int query_autoload()
{
        return 1;
}

