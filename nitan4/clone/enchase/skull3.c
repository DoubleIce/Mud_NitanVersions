// skull.c ����ͷ

#include <ansi.h>
inherit INLAID;

void create()
{
        set_name(HIB "����ͷ" NOR, ({ "skull3" }) );
        set_weight(30);
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("long", BLU "һ��ð������ɫ��â������ͷ�������Բ�ͬѰ���ĸо���\n" NOR);
                set("value", 120000);
                set("unit", "��");
                set("no_identify", 1);
        }
        setup();
}
