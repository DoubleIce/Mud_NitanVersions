// corpse.c 华英雄的尸体(孤星特殊物件载体）

inherit ITEM;

void create()
{
	set_name("腐烂的尸体", ({ "corpse" }));
	set_weight(5000);
	set_max_encumbrance(1000000);
	if (clonep())
		set_default_object(__FILE__);
	else {
		set("unit", "具");
		set("long", "一具腐烂的尸体，似乎怀里揣着什么东西。\n");	
              set("no_sell",1);
	       set("value", 1000);
	}
}

int is_container() { return 1; }
