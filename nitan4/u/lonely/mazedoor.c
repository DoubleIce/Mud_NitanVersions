
#include <ansi.h>
inherit ITEM;

void create()
{
                
        set_name(HIC"迷宫副本传送门"NOR, ({ "maze door"}) );
        set_weight(5);
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("long", HIB"目前的功能有：\n"+
                            "enter <迷宫代码>：创建一个属于自己的迷宫副本。\n"+
                            "迷宫代码：forest-原始森林，icecave-冰窟，darkhole-诡异洞穴，desert-无尽沙漠，temple-失落神庙，deathvalley-死亡峡谷，???-群魔岛，???-诸神殿 。\n"+
                            "\n"NOR); 
                set("unit", "个");
                set("no_get",1);
                set("value", 20);
        }
        setup();
}

void init()
{
        add_action("do_enter","enter");
}

int do_enter(string arg) {
        
        if( !arg || arg == "" )
                return 0;
                
        FUBEN_D->enter_fuben(this_player(), arg);
        return 1;
}


