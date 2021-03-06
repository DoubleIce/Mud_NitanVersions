#include <ansi.h>
inherit ROOM;

void check_mingzhu();

void create()
{
        set("short", "廊道尽端");
        set("long", @LONG 
尽端是道钢门(men)，还有个钢环，门外两侧各嵌着
四颗青光闪亮的明珠(zhu)，光度虽不强，已足可令两人
视物如白昼,门侧左壁光滑的花岗石壁(wall)似乎被人以
匕首一类的东西硬刻出一行字。 
LONG); 
        set("item_desc", ([ 
                "men" : "这扇钢门的钢环似乎可以拉(pull huan)出来!\n",   
                "zhu" : "夜明珠似乎可以拿(pick)出来!\n", 
                "wall" : HIB"「高丽罗刹女曾到此一游」!\n"NOR,
        ]));
        set("exits", ([
                "south" : __DIR__"langdao",
        ]));        
        setup();
}

void init()
{
        add_action("do_pick", "pick");
        add_action("do_pull", "pull");
        add_action("do_zhuan", "zhuan");
}

int do_pick(string arg)
{
        object zhu, me = this_player();
        if ( !arg || arg != "zhu" ) 
                return notify_fail("你是要(pick zhu)吗？\n");
      
        if ( me->query("reborn_start/ygbz/mingzhu") < 4)
        {           
                message_vision(HIG"$N拿下了一颗夜明珠。\n"NOR, me);
                zhu = new(__DIR__"obj/zhu");
                zhu->move(me);  
                me->add("reborn_start/ygbz/mingzhu",1);
                message("vision", HBRED HIB"【宝藏传闻】" + me->query("name") +
                        "在杨公宝库里偷拿了一颗夜明珠!\n"NOR, users());
                check_mingzhu();
                return 1;
        } else
                return notify_fail("夜明珠已经被人拿完了!\n");
}

void check_mingzhu()
{
        object me;
        me = this_player();

        if( me->query("reborn_start/ygbz/mingzhu") >= 4 )
        {
                message_vision(HIC"\n突然$N的脚底下出现一个洞，$N掉了下去。\n\n"NOR, me);

                message("vision", HBRED HIW"【宝藏传闻】" + me->query("name") + 
                        "因为太贪心拿光了夜明珠，被机关踢出宝库了!\n"NOR, users());
                me->unconcious();
                me->move("/d/changan/bei-chengmen");
        }
}

int do_pull(string arg)
{
        object me;
        me = this_player();
        if( !arg || arg != "huan" ) return notify_fail("你是要拉(huan)吗？\n");
           
        message_vision(HIB"$N一把将门环拉後，露出连着钢环的钢索。\n"NOR, me); 

        write(HIC"\n门环似乎可以往左右转动，到底转哪边好呢? \n\n"NOR);
        me->set_temp("lamen", 1);
        return 1;
       
}

int do_zhuan(string dir)
{
        object me;        
        me = this_player();

        if (!me->query_temp("lamen")) 
                return 0;

        if ( !dir || dir != "left" && dir != "right") 
                return notify_fail("你要(zhuan left 还是 right)？\n");
     
        if ( dir == "left" ) 
        {
                message_vision(HIC"$N把门环往左转了一转。\n"NOR, me); 
                add("zhuanmen", 1); 
        }

        if( dir=="right" ) 
        {
                message_vision(HIC"$N把门环往右转了一转。\n"NOR, me); 
                add("zhuanmen", -1); 
                if (query("zhuanmen") < -4 ) 
                set("zhuanmen", 1);
        } 

        if( query("zhuanmen") > 3  &&  !query("exits/enter") ) 
        {
                tell_room(this_object(), HIR"只听「叮」的一声，清脆响亮，"
                          "门慢慢的打开了。\n");
                set("exits/enter", __DIR__"langdao2");
                delete("zhuanmen");
                me->delete_temp("lamen");
                remove_call_out("close");
                call_out("close", 8, this_object());
        }
        return 1;
}

void close(object room)
{
        tell_room(room, HIW"突然出现咔咔的响声，钢门又合上了!\n"NOR);
        room->delete("exits/enter");
}

