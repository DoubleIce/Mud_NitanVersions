// 自由女神像第一层

#include <ansi.h> 
inherit ROOM;

void create()
{
	set("short", "自由女神像第一层");
	set("long", @LONG
这里是自由女神像第一层。
LONG );
	set("exits", ([		
		"out"        : __DIR__"newyork",
              "up"        : __DIR__"floor2",
	]));
	set("no_fight",1);	
       set("no_sleep_room",1); 
       set("no_ride",1);		
	setup();	
}

int valid_leave(object me, string dir)
{
	int c_skill;

	me = this_player();
       if ( ! me->is_player() ) return 1;

	if (dir == "up" )
	{
		c_skill = (int)me->query_skill("dodge", 1);
                if (me->query("qi") > 20)
                {    if (c_skill < 100 ) 
                     {   
                         me->receive_damage("qi", 10 + random(10));
		           tell_object(me,"你爬上一层楼，感觉有些累了。\n");
        		    if (me->can_improve_skill("dodge") )
                        {                        
        		        me->improve_skill("dodge", 20 + c_skill / 5);
        		        tell_object(me,"你感觉似乎觉得腿脚更灵便了。\n");
                         }
                      }
                } else
                {                       
        		   tell_object(me,"你是在爬不动了。\n");
                        return -1;
                }
	}
	return 1;
}


