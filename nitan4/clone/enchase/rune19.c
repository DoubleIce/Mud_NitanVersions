//rune19.c

// Fal ����

#include <ansi.h>

inherit INLAID;

int is_rune() { return 1; }
 
void create()
{
        set_name(HIW "����" NOR, ({ "rune fal", "rune19", "rune"}));
        set_weight(10);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("long", "���ģ�����(FAL)�����Է��밼����Ʒ��\n");
                set("unit", "��");
                set("enchase/SN", 19);
                set("enchase/type", "all");
                set("enchase/consistence", 100); 
                set("enchase/weapon_prop", ([
                        "str"   : 15,               
                ]));
                set("enchase/armor_prop", ([
                        "str"   : 10,     
                ]));
                set("value", 20000);
        }
        setup();
}

int query_autoload() { return 1; }
