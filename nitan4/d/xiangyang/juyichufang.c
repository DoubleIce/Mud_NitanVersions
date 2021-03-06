// Room: /d/xiangyang/juyichufang.c
// Date: Jan. 8 1999 by Winder

inherit ROOM;

void create()
{
	set("short", "厨房");
        set("long", @LONG
这儿是聚义馆的厨房，一般只有白天有几个烧饭师傅在烧火做饭，
供应（serve）伙食，到了晚上就看你的运气了。
LONG );
	set("exits", ([
		"north" : "/d/xiangyang/juyihuayuan",
	]));
        set("objects", ([
                "/d/xiangyang/npc/shaofanshifu"   : 1,
        ]));
	set("no_fight", 0);
	set("ricewater", 30);
	set("coor/x", -320);
	set("coor/y", -120);
	set("coor/z", 0);
	setup();
}

int valid_leave(object me, string dir)
{
	if ( present("soup", me) || present("rice", me))
	return notify_fail("烧饭师傅瞪着一双怪眼：吃不了要兜着走啊？\n");
	return ::valid_leave(me, dir);
}

void init()
{
        add_action("do_serve","serve");
}

int do_serve()
{
	object me;
	object food;
	object water;
	me=this_player();
        if(present("rice",this_player()) ) 
		return notify_fail("烧饭师傅道：吃完了再拿，别浪费食物。\n");
        if(present("rice",this_object()) ) 
		return notify_fail("烧饭师傅道：吃完了再拿，别浪费食物。\n");
	if (query("ricewater")>0)
	{
		message_vision("烧饭师傅给$N一碗高粱米饭和一碗野菜汤。\n",me);
		food=new("/d/xiangyang/obj/rice");
		water=new("/d/xiangyang/obj/soup");
		food->move(me);
		water->move(me);
		add("ricewater",-1);
	}
	else 
		message_vision("烧饭师傅对$N歉声道: 嗨，吃的喝的都没了。\n",me);
	return 1; 
}
void reset()
{
        ::reset();
        set("ricewater",1);
}
