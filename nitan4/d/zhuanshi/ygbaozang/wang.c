#include <ansi.h> 
inherit ROOM;


void create()
{
        set("short", "网中");
        set("long", @LONG 
这是一个大网,由于年代久远,好象已出现朽腐的情况,
虽然可以很容易的挣(zheng)开, 但是下面是个无底洞, 
四周都是钢壁!这张大网似乎可以来回晃动(huang)。
LONG
        );
       set("no_fight",1);
       setup();
}

void init()
{
                
    add_action("do_piao", "huang"); 
    add_action("do_zheng", "zheng");
}

int do_piao(string arg)
{
    object me; 
    me = this_player();

    if( !arg || arg != "wang" )
    { 
       write("你是要晃动(wang)吗？\n");
       return 1;
    }
    message_vision("$N使尽晃动大网，让网来回飘动。\n\n", me);

    me->set_temp("piaowang", 1);
    return 1;
}
     
int do_zheng(string arg)
{
    object me;
    me = this_player();

    if (!arg || arg != "wang" ) 
       return notify_fail("你是要挣脱(wang)吗？\n");
 
    if (me->query_temp("piaowang") ) 
    {
       message_vision(HIY"$N使颈挣动，网寸寸碎裂。\n\n"NOR, me);
       message_vision(HIB"$N凌空提气，借着汤势，如脱笼之鸟，"
            "灵巧的往钢板所在扑去。\n$N成功吸附在钢板"
            "两旁凹凸岩壁的洞壁处。\n\n"NOR, me);
       me->delete_temp("piaowang"); 
       me->move(__DIR__"qiangbi");
       return 1;
    }
    else 
      message_vision(HIY"$N使颈挣扎，但是网始终纹丝不动，\n"
                    "似乎应该先(huang)几下。\n\n"NOR, me);
    return 1;
}

