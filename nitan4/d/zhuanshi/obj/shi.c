// ת������֮ Ů�ʯ 
// Create by yuchang

#include <ansi.h>

inherit ITEM;

int is_magic_item() { return 1; }

void create()
{
        set_name(NOR + YEL + "Ů�ʯ" NOR, ({ "nvwa shi", "nvwa", "shi" }) );
        set_weight(50);
        if (clonep())
                set_default_object(__FILE__);
        else
        {
                set("unit", "��");
                set("long", NOR + YEL "����һ�鷺���߲ʹ�â��ʯͷ����˵��ʯ��Ů洵�"
                                      "�������\n"
                                      "ֻҪ�������������󲻻ᶪʧ���飬Ǳ���Լ����ܡ�\n"
                                      "���������ߺ󲻶�ʧ��\n" NOR);

        }
        setup();
}

