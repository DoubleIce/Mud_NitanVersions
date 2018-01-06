// This program is a part of NITAN MudLIB

#include <ansi.h>
inherit ITEM;

void create()
{
        set_name(HIY "��Ч������" NOR, ({ "study card", "card" }) );
        set_weight(15);  
        if( clonep() ) 
                set_default_object(__FILE__);
        else {
                set("unit", "��");
                set("long", HIY "����һ��˫�����鿨��ʹ����(use)���Ի��2��Сʱ�ĸ�Ч������\n" NOR);
                set("value", 1);
        }
}

void init() 
{
        add_action("do_use", "use");
}

int do_use(string arg)
{
        object me;
        
        if( !arg || !id(arg) )
                return notify_fail("��Ҫʹ��ʲô��\n");
     
        me = this_player();

        message_vision("$N��ʼʹ��˫����������Ϊ�Լ�������2��Сʱ�ĸ�Ч������\n", me);

        me->add("time_reward/study", 7200);
        destruct(this_object());
        return 1;
}

