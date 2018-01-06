#include <ansi.h>

inherit INLAID;

void create()
{
        set_name(HIR "��֮���顤��" NOR, ({"huo jingling", "huo", "jingling"}));
        set_weight(300);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("long", HIR "����ף��֮���ӵ���Ż����Ե����������\n" NOR);
                set("unit", "��");
                set("value", 12000);
                set("can_be_enchased", 1);
                set("enchase/SN", 1 + random(9));
                set("enchase/cur_firm", 100); 
                set("enchase/type", "all");
                set("enchase/weapon_prop", ([
                        "add_fire" : 50,     
                        "add_skill" : 30,     
                ]));
                set("enchase/armor_prop", ([
                        "add_fire" : 50,     
                        "add_skill" : 30,     
                ]));
                set("magic/type", "fire");
                set("magic/power", 90 + random(11));
        }
        setup();
}

int query_autoload()
{
        return 1;
}
