//rune12.c

// Sol ����

#include <ansi.h>

inherit INLAID;

int is_rune() { return 1; }
 
void create()
{
        set_name(HIW "����" NOR, ({ "rune sol", "rune12", "rune"}));
        set_weight(10);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("long", "���ģ�����(SOL)�����Է��밼����Ʒ��\n");
                set("unit", "��");
                set("enchase/SN", 12);
                set("enchase/type", "all");
                set("enchase/consistence", 100); 
                set("enchase/weapon_prop", ([
                        "add_lighting"    : 24,       
                ]));
                set("enchase/armor_prop", ([
                        "reduce_lighting" : 8,
                ]));
                set("value", 20000);
        }
        setup();
}

int query_autoload() { return 1; }

