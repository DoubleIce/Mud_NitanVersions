//rune11.c

// Amn ��ķ

#include <ansi.h>

inherit INLAID;

int is_rune() { return 1; }
 
void create()
{
        set_name(HIW "����" NOR, ({ "rune amn", "rune11", "rune"}));
        set_weight(10);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("long", "���ģ���ķ(AMN)�����Է��밼����Ʒ��\n");
                set("unit", "��");
                set("enchase/SN", 11);
                set("enchase/type", "all");
                set("enchase/consistence", 100); 
                set("enchase/weapon_prop", ([
                        "eff_qi"   : 200,
                ]));
                set("enchase/armor_prop", ([
                        "eff_qi"   : 100,
                ]));
                set("value", 20000);
        }
        setup();
}

int query_autoload() { return 1; }

