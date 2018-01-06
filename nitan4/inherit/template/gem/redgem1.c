// $file_name.c                                                 /* COMMENT_ENTRY */
// Create by TEMPLATE_D. $time.                                 /* COMMENT_ENTRY */
// sword.c
// Written by Lonely                                            /* COMMENT_EXIT  */

#include <ansi.h>

inherit INLAID;

void create()
{
//**    set_name("$name", ({ "$id", }));                        /* NAME_ENTRY */
        set_name(RED "宝石" NOR, ({ "red gem", "gem" }));       /* NAME_EXIT  */

        if (clonep())
                set_default_object(__FILE__);
        else
        {
//**            set("$dbase_key", "$dbase_value\n");            /* DBASE_ENTRY */
                set("long", RED "一片红色的宝石。\n" NOR);      /* DBASE_EXIT  */
                set("unit", "块");
                set("wear_msg", HIC "$N" HIC "轻轻地把$n" HIC "戴在头上。\n" NOR);
                set("remove_msg", HIC "$N" HIC "轻轻地把$n" HIC "从头上摘了下来。\n" NOR);
        }

        set_weight(20);   
        setup();        
}

