
#include <ansi.h>
inherit ITEM;

void create()
{
        set_name(BLU "神秘礼包" NOR, ({"shenmi gift", "gift"}));
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("long",
                              "这是一个用金丝制成的礼包，还不快打开(open)看看？\n");
                set("unit", "个");
                set("open_count", 1);
                set("weight", 1000);
        }
}

void init()
{
        add_action("do_open","open");
}

int do_open(string arg)
{
        object ob, me = this_player();
        string *ob_list = ({    // 随机开出物品列表
                "/clone/enchase/rune01",
                "/clone/enchase/rune02",
                "/clone/enchase/rune04",
                "/clone/enchase/rune03",
                "/clone/enchase/rune05",
                "/clone/enchase/rune06",
                "/clone/enchase/rune07",
                "/clone/enchase/rune08",
                "/clone/enchase/rune09",
                "/clone/enchase/rune10",
                "/clone/enchase/rune11",
                "/clone/enchase/rune12",
                "/clone/enchase/rune13",
                "/clone/enchase/rune14",
                "/clone/enchase/rune15",
                "/clone/enchase/rune16",
                "/clone/enchase/rune17",
                "/clone/enchase/rune18",
                "/clone/enchase/rune19",
                "/clone/enchase/rune20",
                "/clone/enchase/rune21",
                "/clone/enchase/rune22",
                "/clone/enchase/rune23",
                "/clone/enchase/rune24",
                "/clone/enchase/rune25",
                "/clone/enchase/rune26",
                "/clone/enchase/rune27",
                "/clone/enchase/rune28",
                "/clone/enchase/rune29",
                "/clone/enchase/blugem1",
                "/clone/enchase/blugem2",
                "/clone/enchase/blugem3",
                "/clone/enchase/blugem4",
                "/clone/enchase/blugem5",
                "/clone/enchase/blugem6",
                "/clone/enchase/blugem7",
                "/clone/enchase/grngem1",
                "/clone/enchase/grngem2",
                "/clone/enchase/grngem3",
                "/clone/enchase/grngem4",
                "/clone/enchase/grngem5",
                "/clone/enchase/grngem6",
                "/clone/enchase/grngem7",
                "/clone/enchase/maggem1",
                "/clone/enchase/maggem2",
                "/clone/enchase/maggem3",
                "/clone/enchase/maggem4",
                "/clone/enchase/maggem5",
                "/clone/enchase/maggem6",
                "/clone/enchase/maggem7",
                "/clone/enchase/redgem1",
                "/clone/enchase/redgem2",
                "/clone/enchase/redgem3",
                "/clone/enchase/redgem4",
                "/clone/enchase/redgem5",
                "/clone/enchase/redgem6",
                "/clone/enchase/redgem7",
                "/clone/enchase/yelgem1",
                "/clone/enchase/yelgem2",
                "/clone/enchase/yelgem3",
                "/clone/enchase/yelgem4",
                "/clone/enchase/yelgem5",
                "/clone/enchase/yelgem6",
                "/clone/enchase/yelgem7",
                "/clone/enchase/skull1",
                "/clone/enchase/skull2",
                "/clone/enchase/skull3",
                "/clone/enchase/skull4",
                "/clone/enchase/skull5",
                "/clone/enchase/skull6",
                "/clone/enchase/skull7",
                "/clone/money/thousand-gold",
                "/clone/gift/puti-zi",
                "/clone/gift/jiuzhuan",
                "/clone/gift/tianxiang",
                "/clone/gift/xuanhuang",
                "/clone/medicine/yuqing",
                "/clone/gift/feidan",
                "/clone/gift/feimao",
                "/d/shenlong/obj/hua4",
                "/clone/item/dizangshi",
                "/clone/item/magicfruit",
                "/clone/gift/perwan",
                "/clone/gift/shenliwan",
                "/clone/gift/xiandan",
                "/clone/gift/xisuidan",
                "/clone/fam/gift/str3",
                "/clone/fam/gift/int3",
                "/clone/fam/gift/con3",
                "/clone/fam/gift/dex3",
                "/d/item/obj/butian",
                "/d/item/obj/tiancs",
        });

        if (! arg || ! id(arg))
                return 0;
        if (query("open_count") > 0)
        {
                message_vision(
 HIY "$N" HIY "小心翼翼的打开神秘礼包，突然一道亮光直冲天际，映出“恭喜发财”，同时包裹内滚出一件东西。\n" NOR, 
                        this_player());
                add("open_count", -1);
                ob = new(ob_list[random(sizeof(ob_list))]);
                ob -> move(me);
                tell_object(me, HIC "\n你获得了一" + ob->query("unit") + ob->name() + HIC "。" NOR);
                ob = new(ob_list[random(sizeof(ob_list))]);
                ob -> move(me);
                tell_object(me, HIC "\n你获得了一" + ob->query("unit") + ob->name() + HIC "。" NOR);
                ob = new(ob_list[random(sizeof(ob_list))]);
                ob -> move(me);
                tell_object(me, HIC "\n你获得了一" + ob->query("unit") + ob->name() + HIC "。" NOR);
                ob = new(ob_list[random(sizeof(ob_list))]);
                ob -> move(me);
                tell_object(me, HIC "\n你获得了一" + ob->query("unit") + ob->name() + HIC "。" NOR);
                ob = new(ob_list[random(sizeof(ob_list))]);
                ob -> move(me);
                tell_object(me, HIC "\n你获得了一" + ob->query("unit") + ob->name() + HIC "。" NOR);
                ob = new(ob_list[random(sizeof(ob_list))]);
                ob -> move(me);
                tell_object(me, HIC "\n你获得了一" + ob->query("unit") + ob->name() + HIC "。" NOR);
                ob = new(ob_list[random(sizeof(ob_list))]);
                ob -> move(me);
                tell_object(me, HIC "\n你获得了一" + ob->query("unit") + ob->name() + HIC "。" NOR);
                ob = new(ob_list[random(sizeof(ob_list))]);
                ob -> move(me);
                tell_object(me, HIC "\n你获得了一" + ob->query("unit") + ob->name() + HIC "。" NOR);
                ob = new(ob_list[random(sizeof(ob_list))]);
                ob -> move(me);
                tell_object(me, HIC "\n你获得了一" + ob->query("unit") + ob->name() + HIC "。" NOR);
                ob = new(ob_list[random(sizeof(ob_list))]);
                ob -> move(me);
                tell_object(me, HIC "\n你获得了一" + ob->query("unit") + ob->name() + HIC "。\n" NOR);

                return 1;
        }
        else 
                return notify_fail("包裹已经被打开过了，里面空空如也，扔了吧。\n");
}

