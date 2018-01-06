#include <ansi.h>
inherit ITEM;

int query_autoload() { return 1; }
void create()
{
        set_name(HIM "Īаʥ��" NOR, ({ "moye charm", "charm" }));
        set_weight(3000);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("long", HIM "Īаʥ�����Խ���ͨ��������(into)Ϊ���߲�����Ʒ��\n" NOR);
                set("unit", "��");
                set("value", 500000);
        }
        setup();
}

void init()
{
        add_action("do_integrate", "into");
}

int do_integrate(string arg)
{
        object me;
        object ob;

        if (! arg)
                return notify_fail("��Ҫ��ʲô������ʹ�ø�ʥ����\n");

        me = this_player();
        if (! objectp(ob = present(arg, me)) &&
            ! objectp(ob = present(arg, environment(me))))
                return notify_fail("�����Ϻ͸���û���������߰���\n");
        
        if (ob == this_object() || ob->is_character())
                return notify_fail("����Ҫ��ʲô?\n");
                
        if (ob->query_autoload())
                return notify_fail(ob->name() + "�Ѿ������߲�����Ʒ�ˣ�û�������Ҫ�ɣ�\n");

        ob->set("setdbase", 1);
        ob->set("autoload", 1);

        tell_object(me, "���" + name() + "����" + ob->name() + "�ϣ�Ȼ����������дʣ�"
                        "ֻ��ʥ������һ��������" + ob->name() + "���ڣ�\n");

        tell_object(me, HIC "�����" + ob->name() + HIC"�����˲��������ı仯��\n" NOR);

        destruct(this_object());
        return 1;
}
