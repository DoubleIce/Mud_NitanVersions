#include <ansi.h>
inherit ITEM;

void create()
{
        set_name(MAG "�����" NOR, ({ "bindable charm", "charm" }));
        set_weight(3000);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("long", MAG "�÷��Ŀ��Խ���Ʒ����(bind)ӵ��ֱ�Ӱ����ԡ�\n" NOR);
                set("unit", "��");
                set("value", 500000);
        }
        setup();
}

void init()
{
        add_action("do_bind", "bind");
}

int do_bind(string arg)
{
        object me;
        object ob;

        if (! arg || arg == "")
                return notify_fail("��Ҫ��ʲô������ʹ�ø������\n");
                
        me = this_player();
        if (! objectp(ob = present(arg, me)) &&
            ! objectp(ob = present(arg, environment(me))))
                return notify_fail("�����Ϻ͸���û���������߰���\n");
        
        if (ob == this_object() || ob->is_character())
                return notify_fail("����Ҫ��ʲô?\n");
        
        if (sscanf(base_name(ob), "/data/%*s"))       
                return notify_fail("������Ʒ�޷����󶨣�\n");

        ob->set("bindable", 3);
        ob->set("bind_owner", me->query("id"));
        ob->set("setdbase", 1); 
                       
        tell_object(me, "���" + name() + "����" + ob->name() + "�ϣ�Ȼ����������дʣ�"
                        "ֻ��ʥ������һ��������" + ob->name() + "���ڣ�\n");

        tell_object(me, HIC "�����" + ob->name() + HIC"�����˲��������ı仯��\n" NOR);

        destruct(this_object());
        return 1;
}

int query_autoload()
{
        return 1;
}



