#include <ansi.h>

inherit INLAID;

void create()
{
        set_name(YEL "ϡ����ʯ" NOR, ({ "yel gem3","gem3" }));
        set_weight(20);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("long", YEL "һ�Żƹ������ľ�����ʯ�������Բ�ͬѰ���ĸо���\n" NOR);
                set("unit", "��");
                set("value", 120000);
                set("no_identify", 1);
                set("wear_msg", HIC "$N" HIC "����ذ�$n" HIC "����ͷ�ϡ�\n" NOR);
                set("remove_msg", HIC "$N" HIC "����ذ�$n" HIC "��ͷ��ժ��������\n" NOR);                   
        }
        setup();
}

int query_autoload()
{
        return 1;
}
