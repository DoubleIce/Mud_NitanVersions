// ת������֮ ���Ȧ
// Create by Yuchang

#include <ansi.h>

inherit ITEM;

int is_magic_item() { return 1; }

void create()
{
        set_name(HIM + "���Ȧ" NOR, ({ "jinggang quan", "jianggang", "quan" }) );
        set_weight(300);
        if (clonep())
                set_default_object(__FILE__);
        else
        {
                set("unit", "��");
                set("long", HIM "����һ��ӵ�����ǻ���֮���ı����ʱ�ش���Ͷ���\n"
                                "����Ĺ�â��\n" NOR);

        }
        setup();
}

