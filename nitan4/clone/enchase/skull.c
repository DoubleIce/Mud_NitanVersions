// skull.c ����ͷ

#include <ansi.h>
inherit INLAID;

void create()
{
	set_name(HIB "����ͷ" NOR, ({ "skull" }) );
	set_weight(30);
	if( clonep() )
		set_default_object(__FILE__);
        else {
	        set("long", HIB "һ��ð������ɫ��â������ͷ��\n" NOR);
                set("value", 20000);
		set("unit", "��");
                set("no_identify", 1);
	}
        setup();
}

