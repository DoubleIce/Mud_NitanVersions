//rune14.c

// Dol �ࠖ

#include <ansi.h>

inherit INLAID;

int is_rune() { return 1; }
 
void create()
{
        set_name(HIW "����" NOR, ({ "rune dol", "rune14", "rune"}));
        set_weight(10);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("long", "���ģ��ࠖ(DOL)�����Է��밼����Ʒ��\n");
                set("unit", "��");
                set("enchase/SN", 14);
                set("enchase/type", "all");
                set("enchase/consistence", 100); 
                set("enchase/weapon_prop", ([
                        "add_magic"     : 24,                 
                ]));
                set("enchase/armor_prop", ([
                        "reduce_magic"  : 8,
                ]));
                set("value", 20000);
        }
        setup();
}

int query_autoload() { return 1; }

