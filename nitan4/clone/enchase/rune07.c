//rune07.c

// Tal ����

#include <ansi.h>

inherit INLAID;

int is_rune() { return 1; }
 
void create()
{
        set_name(HIW "����" NOR, ({ "rune tal", "rune07", "rune"}));
        set_weight(10);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("long", "���ģ�����(TAL)�����Է��밼����Ʒ��\n");
                set("unit", "��");
                set("enchase/SN", 7);
                set("enchase/type", "all");
                set("enchase/consistence", 100); 
                set("enchase/weapon_prop", ([
                        "suck_jing"   : 1000,
                ]));
                set("enchase/armor_prop", ([
                        "jing_damage" : 500,
                ]));
                set("value", 20000);
        }
        setup();
}

int query_autoload() { return 1; }

