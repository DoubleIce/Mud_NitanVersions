//rune06.c

// Ith ��˾

#include <ansi.h>

inherit INLAID;

int is_rune() { return 1; }
 
void create()
{
        set_name(HIW "����" NOR, ({ "rune ith", "rune06", "rune"}));
        set_weight(10);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("long", "���ģ���˾(ITH)�����Է��밼����Ʒ��\n");
                set("unit", "��");
                set("enchase/SN", 6);
                set("enchase/type", "all");
                set("enchase/consistence", 100); 
                set("enchase/weapon_prop", ([
                        "suck_qi"    : 1500,
                ]));
                set("enchase/armor_prop", ([
                        "qi_damage"  : 800,
                ]));
                set("value", 20000);
        }
        setup();
}

int query_autoload() { return 1; }

