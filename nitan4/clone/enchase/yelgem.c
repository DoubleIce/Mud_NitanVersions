#include <ansi.h>
inherit INLAID;


void create()
{
        set_name(YEL "��ʯ" NOR, ({ "yel gem", "gem" }));
        set_weight(30);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("long", YEL "һ����˸�������â�Ļ�ɫ��ʯ��\n" NOR);
                set("unit", "��");
                set("value", 100000);
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


