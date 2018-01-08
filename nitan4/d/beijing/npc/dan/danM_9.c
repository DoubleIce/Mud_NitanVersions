#include <ansi.h>

inherit COMBINED_ITEM;

void create()
{
        set_name(HIW"�϶��ɵ�"NOR, ({"change dan", "dan"}));
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("base_unit", "��");
                set("no_drop", "�������������뿪�㡣\n");
                set("no_sell", "�������������뿪�㡣\n");
                set("no_put", "�����������ܷ����Ƕ���\n");
                set("no_get", "�������������뿪�Ƕ���\n");
                set("no_steal", "�������������뿪�Ƕ���\n");
                set("no_beg", "�������������뿪�Ƕ���\n");
                set("base_value", 0);
                set("only_do_effect", 1);
        }
        setup();
        set_amount(1);
}

int do_effect(object me)
{
        mapping my;

        if (time() - me->query_temp("last_eat/dan(M)") < 400)
        {
                write("��շ��ù�ҩ����ҩ�Է�����Ч���Ժ���ܼ������á�\n");
                return 1;
        }

        my = me->query_entire_dbase();

//        me->set_temp("last_eat/dan(M)", time());

        if (me->improve_jingli(5))
        {
                message_vision(HIW "$N����һ���϶��ɵ����е�������Ϊ����ǰ��߲��١�\n" NOR, me);
                me->set("jingli", me->query("max_jingli"));
        } else
                message_vision(HIC "$N����һ���϶��ɵ����о�����ûʲôЧ����\n" NOR, me);

//        me->start_busy(2);
        me->start_busy(1);

        add_amount(-1);
        if (query_amount() < 1)
                destruct(this_object());

        return 1;
}

void owner_is_killed()
{
        destruct(this_object());
}