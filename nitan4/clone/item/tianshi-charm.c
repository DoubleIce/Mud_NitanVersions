#include <ansi.h>
inherit ITEM;

void create()
{
        set_name(HIM "天师护身符" NOR, ({ "tianshi charm", "charm" }));
        set_weight(3000);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("long", HIR "此符文具有保护玩家死亡无损失之功能，必须死亡前放在身上。\n" NOR);
                set("unit", "张");
                set("value", 500000);
        }
        set("autoload", 1);
        setup();
}

