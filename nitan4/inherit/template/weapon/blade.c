// $file_name.c                                         /* COMMENT_ENTRY */
// Create by TEMPLATE_D. $time.                         /* COMMENT_ENTRY */
// axe.c
// 自动创建斧头的基准文件。                               /* COMMENT_EXIT  */

#include <weapon.h>

inherit BLADE;

#include <template/weapon.h>

void create()
{
//**    set_name("$name", ({ "$id", }));                /* NAME_ENTRY */
        set_name("刀", ({ "blade", }));                 /* NAME_EXIT  */

        if (clonep())
                set_default_object(__FILE__);
        else
        {
//**            set("$dbase_key", "$dbase_value\n");    /* DBASE_ENTRY */
                set("long", "这是一柄普通的刀。\n");  /* DBASE_EXIT  */
                set("unit", "柄");
                set("value", 200);
                set("material", "steel");
                set("wield_msg", "$N「唰」的一声抽出一柄$n握在手中。\n");
                set("unwield_msg", "$N将手中的$n收回刀鞘。\n");
        }

//**    $function_name($argument);                      /* FUNCTION_ENTRY */
        set_weight(5000);
        init_blade(5, 2);                                 /* FUNCTION_EXIT  */
        setup();
}

mixed hit_ob(object me, object victim, int damage_bonus)
{
        if (me->query("kar") > 20)
        {
                // return ITEM_D->weapon10lv_hit_ob(me, victim, this_object(), damage_bonus*2);
                return ITEM_D->weapon_hit_ob(me, victim, this_object(), damage_bonus*2);
        } else
                return "$N呼唤手中的" + query("name") + "，试图心神合一，" +
                       "却感到力不从心。\n";
}
