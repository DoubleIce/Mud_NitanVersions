#include <ansi.h> 

inherit BOOK;

void create()
{
   set_name("�����羪�ƽ���", ({ "lubabyer-sword book" }));
        set_weight(500);
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("unit", "��");
		set("long", "����һ���ñ���д�ɵ��顣���飺�����羪�ƽ�����\n��������Ľ�ݺ���(lubabyer)��\n");
                set("value", 1);
                set("autoload", 1);
                set("material", "silk");
                set("skill", ([
			"name": "lubabyer-sword",
                        "exp_required": 100000,
                        "jing_cost" :  40,
                        "difficulty": 100,
                        "max_skill" :  199,
                        "min_skill" :  0
                ]) );
        }
}
