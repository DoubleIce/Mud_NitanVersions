// 转世神器之 女娲石 
// Create by yuchang

#include <ansi.h>

inherit ITEM;

int is_magic_item() { return 1; }

void create()
{
        set_name(NOR + YEL + "女娲石" NOR, ({ "nvwa shi", "nvwa", "shi" }) );
        set_weight(50);
        if (clonep())
                set_default_object(__FILE__);
        else
        {
                set("unit", "块");
                set("long", NOR + YEL "这是一块泛着七彩光芒的石头，传说此石乃女娲的"
                                      "护身符。\n"
                                      "只要带在身上死亡后不会丢失经验，潜能以及技能。\n"
                                      "此神器下线后不丢失。\n" NOR);

        }
        setup();
}

