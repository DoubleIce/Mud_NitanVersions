// cjade.c ����Ƭ

#include <ansi.h>
#include <armor.h>

inherit HEAD;

int is_enchase_ob(){ return 1; }

void create()
{
	set_name(HIG "����Ƭ" NOR, ({ "chipped jade" }) );
	set_weight(25);
	if( clonep() )
		set_default_object(__FILE__);
	else {
                set("long", HIG "һƬ��Ө��͸���������Ƭ��\n" NOR);
                set("value", 20000);
		set("unit", "Ƭ");
                set("armor_prop/per", 3);
                set("no_identify", 1);
		set("wear_msg", HIC "$N" HIC "����ذ�$n"
                    HIC "����ͷ�ϡ�\n" NOR);
                set("remove_msg", HIC "$N" HIC "����ذ�$n"
                    HIC "��ͷ��ժ��������\n" NOR);
	}
        setup();
}

