#include <ansi.h>
inherit ITEM;

void create()
{
        set_name(HIM "PK��ʱ��" NOR, ({ "pk remind", "remind" }));
        set_weight(3000);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("long", HIR "�˷��ľ���������Ҷ�PK�������֮���ܡ�\n" NOR);
                set("unit", "��");
                set("value", 500000);
        }
        setup();
}

int query_autoload()
{
        return 1;
}

