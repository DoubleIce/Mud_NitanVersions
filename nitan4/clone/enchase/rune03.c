//rune03.c

// Tir �ؠ�

#include <ansi.h>

inherit INLAID;

int is_rune() { return 1; }
 
void create()
{
        set_name(HIW "����" NOR, ({ "rune tir", "rune03", "rune"}));
        set_weight(10);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("long", "���ģ��ؠ�(TIR)�����Է��밼����Ʒ��\n");
                set("unit", "��");
                set("enchase/SN", 3);
                set("enchase/type", "all");
                set("enchase/consistence", 100); 
                set("enchase/weapon_prop", ([
                        "derive_times"  : 20,                 
                ]));
                set("enchase/armor_prop", ([
                        "derive_times"  : 10,       
                ]));
                set("value", 20000);
        }
        setup();
}

int query_autoload() { return 1; }

