// 转世神器之 金刚圈
// Create by Yuchang

#include <ansi.h>

inherit ITEM;

int is_magic_item() { return 1; }

void create()
{
        set_name(HIM + "金刚圈" NOR, ({ "jinggang quan", "jianggang", "quan" }) );
        set_weight(300);
        if (clonep())
                set_default_object(__FILE__);
        else
        {
                set("unit", "个");
                set("long", HIM "这是一个拥有吸星换月之力的宝物，不时地从中投射出\n"
                                "奇异的光芒。\n" NOR);

        }
        setup();
}

