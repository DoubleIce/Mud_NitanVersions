#include <ansi.h>

inherit INLAID;

void create()
{
        set_name(HIG "ʥ֮��ʯ" NOR, ({ "grn gem5","gem5" }));
        set_weight(30);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("long", HIG "һ����˸�������â����ɫ��ʯ��"
                    "���˸е�һ������ļ¡�\n" NOR);
                set("unit", "��");
                set("value", 160000);
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