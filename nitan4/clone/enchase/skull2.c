// skull.c ����ͷ

#include <ansi.h>
inherit INLAID;

void create()
{
        set_name(HIB "����ͷ" NOR, ({ "skull2" }) );
        set_weight(30);
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("long", BLU "һ��ð������ɫ��â������ͷ��������ȱ��˿�����ơ�\n" NOR);
                set("value", 100000);
                set("unit", "��");
                set("no_identify", 1);
        }
        setup();
}
