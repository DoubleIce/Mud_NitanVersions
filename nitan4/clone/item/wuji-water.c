// ����ʥˮ���ڿ��ױ���

#include <ansi.h>

inherit ITEM;

void create()
{
        set_name(HIM "�޼�ʥˮ" NOR, ({ "wuji water", "water" }) );
        set_weight(30);

        if (clonep())
                set_default_object(__FILE__);
        else {
                set("long", HIW "һƿӨ��͸ʥˮ��ɢ���ѤĿ�Ĺ�ʡ�\n"
                            "����������ֱ����չ(kuokong)�����������������\n" NOR);
                set("value", 1);
                set("no_sell", 1);
                set("unit", "ƿ");
        }

        setup();
}

void init()
{
        add_action("do_kuokong", "kuokong");
}

int do_kuokong(string arg)
{
        object me;
        object ob;

        if (! arg)
                return notify_fail("��Ҫ��ʲô������ʹ���޼�ʥˮ��\n");

        me = this_player();
        if (! objectp(ob = present(arg, me)) &&
            ! objectp(ob = present(arg, environment(me))))
                return notify_fail("�����Ϻ͸���û���������߰���\n");
        
        if (ob == this_object() || ob->is_character())
                return notify_fail("����Ҫ��ʲô?\n");
        
        if (! ob->is_item_make())
                return notify_fail(ob->name() + "�޷����޼�ʥˮ����չ���ۡ�\n");
        
        if (! ob->query("enchase/flute"))
                return notify_fail("�㻹����ȥ���׺��ٿ�����չ���۰ɡ�\n");
                
        ob->set("ultimate/37", 1);
        ob->set("ultimate/39", 1);
        
        if (ob->query("skill_type") 
        ||  (ob->query("armor_type") && ob->query("armor_type") == "hands"))
                ob->set("enchase/flute", 9);                                      
        else
                ob->set("enchase/flute", 7);
        
        ob->save();
        tell_object(me, "���һƿ" + name() + "����" + ob->name() + "�ϣ�"
                        "ֻ��" + ob->name() + "ͨ����һ�����𣬻�Ȼ�Ѿ�����������ۣ�\n");

        destruct(this_object());
        return 1;
}

