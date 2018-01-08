// ת������֮ ħ��
// Create by yuchang

#include <ansi.h>

#include <armor.h> 
inherit CLOTH; 

int is_magic_item() { return 1; }

void create()
{
        set_name(NOR + WHT + "ħ��" NOR, ({ "mo jie", "mojie", "jie" }) );
        set_weight(800);
        if (clonep())
                set_default_object(__FILE__);
        else
        {
                set("unit", "ö");
                set("long", NOR + WHT "����һö��˵�еĽ�ֻ��������ѣĿ�Ĺ⻪����\n"
                                      "˵�������˷���Ϊ�˴�ͨ��ؽ��紦���á�\n"
                                      "����֮����(chuansong)��գ�����̫�龳�硣\n" NOR);
                set("material", "steel");
                set("wear_msg", NOR + WHT "$N" NOR + WHT "��ħ�������ָ����ʱһ"
                                           "������������\n" NOR);
                set("remove_msg", NOR + WHT "$N" NOR + WHT "��ħ�����ָ��ȡ������\n" NOR);

        }
        setup();
}

void init()
{
        add_action("do_chuansong", "chuansong");       
}

int do_chuansong(string arg)
{
        object me;
        
        me = this_player();
        
        if(! objectp(present("mo jie", me)))return 0;
        
        if (me->is_fighting() || me->is_busy())
                 return notify_fail("����æ�أ�\n");
        
        if (! environment(me)->query("outdoors"))
                 return notify_fail("����ȵ�����ȥ��\n");
                 
        message_sort(NOR + WHT + "\n$N" NOR + WHT "����˫�����е�ħ�䷢��ҫ�����⣬"
                     "ɲ�Ǽ������¶��һ���Ѻۣ�ħ�仯��һ������Ĺ�â��$N" NOR + WHT +
                     "���̫��֮�С�\n" NOR, me);
                
        me->move("/d/zhuanshi/sky/sky1");
        destruct(this_object());

        return 1;
}

