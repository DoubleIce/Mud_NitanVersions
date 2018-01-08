
#include <ansi.h>  
inherit ROOM;

void create()
{
        set("short", "小宝库");
        set("long", @LONG  
这是一个宽阔的密封地室，室顶四角均有通气口，两边 
平排放置共十多个该是装载奇珍异宝的箱子(xiang),贴墙有
几十个兵器架，放满各种，兵器，但都只是普通货色，且全
部都生锈发霉，拿去送人也没有人要。
LONG); 
        set("item_desc", ([ 
                "xiang" : "箱子里好像有金票，你要拿(na)出来吗?\n",      
        ]));
        set("exits", ([
                "out" : __DIR__"langdao6",
        ]));
        setup();
}
void init()
{
        add_action("do_na", "na"); 
        add_action("do_fan", "fan"); 
}

void check_tishi()
{
        message("vision", HIR"$N在拿金票的时候突然发现箱底的板似乎可以翻!。\n",
                this_object() );
}

int do_na(string arg)
{
        int i;
        object tg, me = this_player();

        if ( !arg || arg != "cash" ) 
                return notify_fail("你是想拿箱子里的金票(cash)吗?\n");

      
        if ( me->query("reborn_start/yanggong/cash") )
        { 
                message_vision("$N伸手去拿箱子里的金票，"
                               "结果发现已经给人拿光了\n", me);       
                return 1;
        }
 
        message_vision(HIY"$N在箱子里拿了一叠金票放到怀里!\n"NOR, me);
        
        for( i = 0; i < 5; i++ )
        {
                tg = new("/clone/money/cash");
                tg->move(me);
        }   
        me->set("reborn_start/yanggong/cash", 1);

        message("vision", HBRED HIW"【宝藏传闻】" + me->query("name") +
                "在杨公宝库里偷拿了一叠金票!\n"NOR,users()); 

        tell_object(me, BLINK HIB"\n你在拿金票的时候"
                       "突然发现箱底的板似乎可以翻(fan)!。\n\n"NOR);

        return 1;       
}

int do_fan(string arg)
{
        object me; 
      
        me = this_player();
        if( !arg || arg != "xiang" ) 
                return notify_fail("你是要翻(xiang)吗？\n");

        message_vision(HIY"$N把箱底的盖子一翻，发现箱子下面另有一番天地!。\n"NOR, me);
  
        set("exits/down", __DIR__"baoku2");
        call_out("close", 5);
        return 1;
}
        
void close()
{
        tell_room(this_object(), HIG"突然出现咔咔的响声，箱底又合上了!\n"NOR);
        delete("exits/down");
}


