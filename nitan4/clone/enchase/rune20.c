//rune20.c

// Lem �{ķ

#include <ansi.h>

inherit INLAID;

int is_rune() { return 1; }
 
void create()
{
        set_name(HIW "����" NOR, ({ "rune lem", "rune20", "rune"}));
        set_weight(10);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("long", "���ģ��{ķ(LEM)�����Է��밼����Ʒ��\n");
                set("unit", "��");
                set("enchase/SN", 20);
                set("enchase/type", "all");
                set("enchase/consistence", 100); 
                set("enchase/weapon_prop", ([
                        "max_neili"     : 15000,    
                ]));
                set("enchase/armor_prop", ([ 
                        "max_neili"     : 7500,  
                ]));
                set("value", 20000);
        }
        setup();
}

int query_autoload() { return 1; }
