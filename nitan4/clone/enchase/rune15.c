//rune15.c

// Hel ����

#include <ansi.h>

inherit INLAID;

int is_rune() { return 1; }
 
void create()
{
        set_name(HIW "����" NOR, ({ "rune hel", "rune15", "rune"}));
        set_weight(10);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("long", "���ģ�����(HEL)�����Է��밼����Ʒ��\n");
                set("unit", "��");
                set("enchase/SN", 15);
                set("enchase/type", "all");
                set("enchase/consistence", 100); 
                set("enchase/weapon_prop", ([
                        "add_cold"    : 24,             
                ]));
                set("enchase/armor_prop", ([
                        "reduce_cold" : 8,
                ]));
                set("value", 20000);
        }
        setup();
}

int query_autoload() { return 1; }

