#include <ansi.h>

inherit INLAID;

void create()
{
        set_name(BLU "ħ֮��ʯ" NOR, ({ "blu gem6", "gem6" }));
        set_weight(40);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("long", BLU "һ����˸�������â����ɫ��ʯ�����˸е�һ������ļ¡�\n" NOR);
                set("unit", "��");
                set("value", 180000);
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
