#include <ansi.h> 

inherit BOOK;

void create()
{
	set_name("����������", ({ "wuming-sword book" }));
        set_weight(500);
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("unit", "��");
		set("long", "����һ���ñ���д�ɵ��顣���飺������������\n�����������Һ�(wxswlhe)��\n");
                set("value", 1);
                set("autoload", 1);
                set("material", "silk");
                set("skill", ([
			"name": "wuming-sword",
                        "exp_required": 100000,
                        "jing_cost" :  40,
                        "difficulty": 100,
                        "max_skill" :  199,
                        "min_skill" :  0
                ]) );
        }
}
