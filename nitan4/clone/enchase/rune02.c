//rune02.c

// Eld ����

#include <ansi.h>

inherit INLAID;

int is_rune() { return 1; }
 
void create()
{
        set_name(HIW "����" NOR, ({ "rune eld", "rune02", "rune"}));
        set_weight(10);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("long", "���ģ�����(ELD)�����Է��밼����Ʒ��\n");
                set("unit", "��");
                set("enchase/SN", 2);
                set("enchase/type", "all");
                set("enchase/consistence", 100); 
                set("enchase/weapon_prop", ([
                        "learn_times"     : 20,                 
                ]));
                set("enchase/armor_prop", ([
                        "learn_times"     : 10,       
                ]));
                set("value", 20000);
        }
        setup();
}

int query_autoload() { return 1; }

