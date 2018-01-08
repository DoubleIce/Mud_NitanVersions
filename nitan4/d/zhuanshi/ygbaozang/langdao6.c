inherit ROOM;
#include <ansi.h> 

void create()
{
        set("short", "�ȵ�");
        set("long", @LONG 
������һ���ȵ�,ĩ��û�밵��������Ѳ�Զ�� 
��ǳ������������Ŀ�����������!

LONG
        );     
        set("exits", ([  
            "enter"  : __DIR__"baoku",
            "north"  : __DIR__"langdao5",
            "south"  : __DIR__"langdao6",
            "west"  : __DIR__"langdao6",
            "east"  : __DIR__"langdao6",
        ]));             
        setup();
}

void init()
{
    object me;
    string msg;
    me = this_player();  

   if ( me->query_skill("dodge",1) >= 620 
        && me->query("neili") > 1000) 
   {
       msg =  HIB"\n$N�粽���ţ���Ȼ�������졣"
             "ʮ֦�س��شֵľ��ּ�ʸ�������������µĴ���һ�˰� "
             "�ڴ�����������ƿ����������ĺ�Х��������ž��ĵ���"
             "�ȵ�������̶���$N����һ�ƣ�����˼�ʸ!" 
             "���ǻ������˲�������!\n\n"NOR;

      message_sort(msg, me);
      me->add("neili", - me->query("max_qi") / 5); 
      if ( me->query("neili") < 0 )
           me->set("neili", 0);
   
  } else
  if ( me->query_skill("dodge",1) >= 600 ) 
  {     
     msg = HIR"$N�粽���ţ���Ȼ�������졣"
           "ʮ֦�س��شֵľ��ּ�ʸ�������������µĴ���һ�˰�"
           "�ڴ�����������ƿ����������ĺ�Х��������ž��ĵ���"
           "�ȵ�������̶���$N������ʸ�����������Ṧ�����ң�����ʸ" 
           "�����ˣ����������!\n"NOR;

     message_sort(msg, me);
     me->set_temp("die_reason", "���Ҽ�������");
     me->receive_wound("qi", me->query("max_qi") / 5);
  }    
  else
  {
    msg = HIR"$N�粽���ţ���Ȼ�������졣"
          "ʮ֦�س��شֵľ��ּ�ʸ�������������µĴ���һ�˰�"
          "�ڴ�����������ƿ����������ĺ�Х��������ž��ĵ���"
          "�ȵ�������̶���$N������ʸ�������Ṧ��������ʱ��" 
          "�����һֻ��⬣�\n"NOR;
     message_sort(msg, me);

    me->set_temp("die_reason", "���Ҽ�������");
    me->die();  
  }
}
