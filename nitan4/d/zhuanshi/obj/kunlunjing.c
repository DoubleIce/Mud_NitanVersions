// �Ϲ����� ���ؾ�

#include <ansi.h>

inherit ITEM;

int is_magic_item() { return 1; }

void create()
{
        set_name(HIW "���ؾ�" NOR, ({ "kunlun jing", "kunlun", "jing" }) );
        set_weight(100);
        if (clonep())
                set_default_object(__FILE__);
        else
        {
                set("unit", "��");
                set("long", HIW "����һ��ͨ������ľ��ӣ�������ѣĿ�Ĺ⻪����˵ӵ�д���ʱ�յ�������\n"              
                                "����֮����(chuansuo)��գ�����̫�龳�硣\n" NOR);

        }

        setup();
}

void init()
{
        add_action("do_chuansuo", "chuansuo");       
}

int do_chuansuo(string arg)
{
        object me;
        
        me = this_player();
              
        if (me->is_fighting() || me->is_busy())
                 return notify_fail("����æ�أ�\n");
        
        if (! environment(me)->query("outdoors"))
                 return notify_fail("����ȵ�����ȥ��\n");

        message_vision(HIW "\n$N" HIW "�������е����ؾ���ɲ�Ǽ�⻪�����$N" HIW "��"
                         "�������â��ʧ����� ����\n" NOR, me);                 
                
        me->move("/d/zhuanshi/sky/sky1");
        destruct(this_object());

        return 1;
}

