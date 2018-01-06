#include <ansi.h>
inherit ITEM;

void create()
{
        set_name(HIM "抽取之符" NOR, ({ "extracte charm", "charm" }));
        set_weight(3000);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("long", HIR "此符文具有见装备中好的附加属性宝石抽取出来的功能。\n"
                           "指令格式： extra <物品> from <道具>\n" NOR);
                set("unit", "张");
                set("value", 500000);
        }
        setup();
}

void init()
{
        add_action("do_extra", "extra");
}

int do_extra(string arg)
{
        object me;
        object ob, obj;
        int    i, n, t, flag;
        string item, what;
        mixed  inset;
        array  apply;
        mapping data, dbase, prop;

        if (! arg)
                return notify_fail("你要往什么道具上使用该圣符？\n");

        if (sscanf(arg, "%s from %s", what, item) != 2)
                return notify_fail("指令格式： extra <物品> from <道具> \n");

        me = this_player();
        if (! objectp(ob = present(item, me)) &&
            ! objectp(ob = present(item, environment(me))))
                return notify_fail("你身上和附近没有这样道具啊。\n");

        if (ob->query("equipped"))
                return notify_fail("你先卸除他先。\n");
        
        t = 0;
        flag = 0;  
        data = ([]);
        prop = ([]);
        dbase = ([]);      
        if (ob->is_item_make() &&
            arrayp(inset = ob->query("enchase/inset")) &&
            (n = sizeof(inset)))
        {

                for (i = 0; i < n; i++)
                        if (inset[i]["id"] == what)
                        {
                                flag = 1;
                                data = inset[i];
                                inset[i] = 0;
                                break;
                        }

                inset -= ({ 0 });
                ob->set("enchase/inset", inset);
                
                if (flag)
                {
                        sscanf(what, "%s &%*s", what);
                        if (strsrch(what, "gem") >= 0)
                                obj = TEMPLATE_D->create_object("/template/gem/gem", what, data, 1);
                        else
                        if (strsrch(what, "skull") >= 0)
                                obj = TEMPLATE_D->create_object("/template/gem/skull", what, data, 1);
                        else
                        {
                                ob->delete("enchase/rune" + data["SN"]);
                                ob->add("enchase/SN", -data["SN"]);
                                ob->add("enchase/used", -1);
                                obj = new("/clone/enchase/rune" + data["SN"]);
                        }

                        prop = ob->query("enchase/apply_prop");
                        dbase = data["enchase_prop"];
                        apply = keys(dbase);
                        for (i = 0; i < sizeof(apply); i++)
                        {
                                t = dbase[apply[i]];
                                if (! undefinedp(prop[apply[i]]))
                                        prop[apply[i]] -= t;
                                else
                                        prop[apply[i]] = -t;
                                        
                                if (prop[apply[i]] == 0)
                                        map_delete(prop, apply[i]);
                        }

                        ob->set("enchase/apply_prop", prop);  
                        ob->save();                      

                        message_vision(HIR "\n只见圣符化作一道红光飞入" + ob->name() + HIR "体内, 一" +
                                obj->query("unit") + obj->name() + HIR "出现在眼前！\n" NOR, me);

                        obj->move(me, 1);
                        destruct(this_object());
                        return 1;
                }
        } else
                return notify_fail("这个物品无法抽取。\n");
}

int query_autoload()
{
        return 1;
}


