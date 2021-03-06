#include <ansi.h> 
inherit ROOM;

void create()
{
        set("short", "秘道终端");
        set("long", @LONG 
这条花岗石建成的秘道，已是巧夺天工，当年不知
动用多少人力物力!左壁有一石突出,似乎可以按(an)
一按!
LONG);
        set("exits", ([
                "north" : __DIR__"tongdao4",
        ]));        
        setup();
}

void init()
{
        add_action("do_an", "an");
}

int do_an(string dir)
{
    object me; 
    object room;       

    me = this_player();

    if ( !dir || dir != "right" && dir != "left")
    { 
       if ( me->query_temp("tongguo" ))      
          return notify_fail(HIM"你要(an right)还是(an left)?\n");
       else
          return notify_fail(HIM"你是要(an right)吗?\n");
    }


   if( dir == "right" ) 
   {
      message_vision("$N按向了右边石壁的那个制钮。\n", me);
      if (me->query_temp("tongguo"))
      {
            message_vision("机括声响起，右方一壁凹进去，现出一个方洞!\n", me);
            me->delete_temp("tongguo");
            set("exits/enter", __DIR__"langdao");
            remove_call_out("close");
            call_out("close", 5);   
            return 1;        
       } else      
       return 0;
  }
  if( dir == "left" ) 
  {
      message_vision(HIW"\n$N把凸出左璧的制钮用力下按,"
                     "「轧轧」声再响。\n\n"NOR, me);
      message_vision(HIW"\n$N身处的一截通道忽然移动起来，"
                     "带着你往下滑行。\n\n"NOR, me);

      remove_call_out("on_wang"); 
      call_out("on_wang", 1, me);
      return 1;
  }
}

void on_wang(object me)
{
    object room; 
    
    message_vision(HIB"$N心叫我命休矣，「轰」的一声，活动通道在俯冲近二十丈後，"
             "\n不知撞在甚麽地方，蓦地煞止。\n"NOR, me);
    message_vision(HIB"你却没有通道煞停的好运道，"
             "给强猛的冲力撞带至茫茫黑暗中另一空间，\n"NOR, me);
    message_vision(HIB"你身子凌空下跌，蓬蓬两声，"
             "分别一头栽进一幅像鱼网般的东西内。\n\n"NOR, me);

    me->move(__DIR__"wang");

    remove_call_out("on_wang2"); 
    call_out("on_wang2", 1, me);
}

        
void on_wang2(object me)
{
    tell_object(me, HIR"弹起又再跌下，震得你浑身酸麻，晕头转向，"
                        "不知人间何世。\n"NOR);
    tell_object(me, HIR"你的噩梦尚未完结，网子忽往下堕，"
             "疾跌近丈後，随跌势网子往下束收，\n"NOR);
    tell_object(me, HIR"到跌定的一刻，刚好把你网个结实，动弹不得\n\n"NOR);
    me->unconcious();
}

void close()
{
      message_vision(HIG"突然出现咔咔的响声，墙壁又合上了!\n\m"NOR,
                     this_object());
      delete("exits/enter");
}

