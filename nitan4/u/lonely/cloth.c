#include <armor.h>
inherit "/u/lonely/armor1";

void create()
{
        set_name("����", ({ "cloth" }));
        set("long", "����һ���ǳ���ͨ�Ĵֲڲ��¡�\n"); 
        set_weight(3000);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("unit", "��");
                set("material", "cloth");
                set("armor_prop/armor", 1);
        }
        setup();
}

