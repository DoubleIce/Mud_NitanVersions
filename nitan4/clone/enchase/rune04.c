//rune04.c

// Nef �Ƿ�

#include <ansi.h>

inherit INLAID;

int is_rune() { return 1; }
 
void create()
{
        set_name(HIW "����" NOR, ({ "rune nef", "rune04", "rune"}));
        set_weight(10);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("long", "���ģ��Ƿ�(NEF)�����Է��밼����Ʒ��\n");
                set("unit", "��");
                set("enchase/SN", 4);
                set("enchase/type", "all");
                set("enchase/consistence", 100); 
                set("enchase/weapon_prop", ([
                        "practice_times"       : 20,
                ]));
                set("enchase/armor_prop", ([
                        "practice_times"       : 10,
                ]));
                set("value", 20000);
        }
        setup();
}

int query_autoload() { return 1; }

