//rune25.c

// Gul �Š�

#include <ansi.h>

inherit INLAID;

int is_rune() { return 1; }
 
void create()
{
        set_name(HIW "����" NOR, ({ "rune gul", "rune25", "rune"}));
        set_weight(10);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("long", "���ģ��Š�(GUL)�����Է��밼����Ʒ��\n");
                set("unit", "��");
                set("enchase/SN", 25);
                set("enchase/type", "all");
                set("enchase/consistence", 100); 
                set("enchase/weapon_prop", ([
                        "avoid_dodge"     : 30,
                ]));
                set("enchase/armor_prop", ([
                        "avoid_attack"    : 8,
                ]));
                set("value", 20000);
        }
        setup();
}

int query_autoload() { return 1; }

