// Written by Lonely@IsMUD.net
// crystal.c 水晶

#include <ansi.h>
#include <armor.h>

inherit INLAID; 

int is_inlaid() { return 1; }
int is_magic_item() { return 1; }

void create()
{
        set_name("黑水晶", ({ "black crystal", "crystal" }) );
        set_weight(30);
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("long", HIC "一块黑色的水晶，可以抽取(extra)宝石中的魔法属性。\n" NOR);
                set("value", 50000);
                set("unit", "块");
                set("autoload", 1);
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
        
        me = this_player();
        
        if( !arg ) return notify_fail("指令格式： extra <属性> from <物品> \n");
                
        if( this_object()->query("enchase") )
                return notify_fail("黑水晶已经抽取过一个属性了。\n");
                
        if( sscanf(arg, "%s from %s", what, item) != 2 )
                return notify_fail("指令格式： extra <属性> from <物品> \n");
                
        if( !objectp(ob = present(item, me)) &&
            !objectp(ob = present(item, environment(me))) )
                return notify_fail("你身上和附近没有这样物品。\n");
                
        if( ob->query("equipped") )
                return notify_fail("你先卸除他先。\n");
                
        if( ob->is_item_make() )
                return notify_fail("自造装备不可以被抽取属性。\n");
        
        if( !ob->query("enchase") )
                return notify_fail("这个物品上面没有可用来抽取的属性。\n");
        
        if( !ob->query("enchase/armor_prop/" + what) &&
            !ob->query("enchase/weapon_prop/" + what) )
                return notify_fail("这个物品上面没有你想抽取的属性。\n");
        
        if( ob->query("enchase/armor_prop/" + what) ) {
                this_object()->set("enchase/armor_prop/" + what, ob->query("enchase/armor_prop/" + what));
                ob->delete("enchase/armor_prop/" + what);     
        } else {
                this_object()->set("enchase/weapon_prop/" + what, ob->query("enchase/weapon_prop/" + what));
                ob->delete("enchase/weapon_prop/" + what);   
        }
        
        this_object()->set("setdbase", 1);
           
        message_vision(HIR "\n一道黑光闪过，似乎有一股神奇的力量附在其中！。\n" NOR, me);
        return 1;
}

