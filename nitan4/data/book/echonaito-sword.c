#include <ansi.h> 

inherit BOOK;

void create()
{
	set_name("「吗来古怪剑」", ({ "echonaito-sword book" }));
        set_weight(500);
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("unit", "本");
		set("long", "这是一本用薄绢写成的书。上书：“吗来古怪剑”。\n书上署名吗来小草(echonaito)。\n");
                set("value", 1);
                set("autoload", 1);
                set("material", "silk");
                set("skill", ([
			"name": "echonaito-sword",
                        "exp_required": 100000,
                        "jing_cost" :  40,
                        "difficulty": 100,
                        "max_skill" :  199,
                        "min_skill" :  0
                ]) );
        }
}
