inherit ROOM;

void create()
{ 
        set("short", "无极帮门前");
        set("long", @LONG
这里是无极帮杭州分部的大门前面，无极帮的这个大厅只是发布
任务的所在，即使如此，这座建筑也造的风格迥然，让人一眼看上去，
就觉得气势不凡。
LONG );
        set("outdoors", "hangzhou");
        set("exits", ([
                "east" :  "/d/hangzhou/road12",
                "west" : "/d/hangzhou/wjb_hzdt",
        ])); 
        set("objects", ([   
             "/d/hangzhou/npc/wjb-guard" : 2,   
            ]));
               
        setup();            
}

int valid_leave(object me, string dir) 
{ 
        if (objectp(present("shou wei", environment(me))) && dir == "west") 
        {
           if (! me->query_temp("good_wjb1") && me->query("bunch/bunch_name") != "无极帮")
               return notify_fail("守卫一把拦住你，朗声喝道：我无极帮怎由闲杂人等随便进出。\n"); 
           else
           {
              me->delete_temp("good_wjb1");
              return ::valid_leave(me, dir);
           }
        }
        return ::valid_leave(me, dir); 
} 

