#include <ansi.h>
inherit ITEM;

void create()
{
        set_weight(100);
        set_name(HIM "�����" NOR, ({"furou gao", "furou", "gao"}));
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("unit", "��");
                set("long", HIM "����һ����ʰ�쵵ľ綾ҩ�࣬��ɱ�������Ρ�\n" NOR);
                set("value", 50);
		set("poison_type", "poison");
                set("can_pour", 1);
                set("can_daub", 1);
                set("can_drug", 1);
                set("poison", ([
                        "level" : 200,
                        "id"    : "he tieshou",
                        "name"  : "�����綾",
                        "duration": 15,
                ]));
                set("no_sell", 1);
		set("only_do_effect", 1);
        }
        setup();
}

int do_effect(object me)
{
        message_vision("$Nһ������������൹�������С�\n", me);
        me->set_temp("die_reason", "���˸����ȥ���ڰ��޳���");
        me->die();
        destruct(this_object());
        return 1;
}
