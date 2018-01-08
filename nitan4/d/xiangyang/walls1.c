// Room: /d/xiangyang/walls1.c
// Date: Jan. 8 1999 by Winder

inherit ROOM;

void create()
{
	set("short", "石阶");
        set("long", @LONG
这是登向城头的石阶，因为城墙很高，所以很陡。石阶两侧有可
供拉车上下的斜坡道。
LONG );
        set("outdoors", "xiangyang");
	set("no_clean_up", 0);

	set("exits", ([
		"westup"   : "/d/xiangyang/walls3",
		"eastdown" : "/d/xiangyang/southgate1",
	]));
	set("coor/x", -300);
	set("coor/y", -130);
	set("coor/z", 10);
	setup();
}
int valid_leave(object me, string dir)
{
        mixed c_exp;
        int c_skill;
	if (dir == "westup" )
	{
		c_exp=me->query("combat_exp");
		c_skill=me->query_skill("dodge",1);
                if (me->query("qi") > 10)
                {
		        me->receive_damage("qi",10);
                            if (count_lt(count_div(count_mul(count_mul(c_skill, c_skill), c_skill), 10), c_exp) && 
                                c_skill < 101) 
		        me->improve_skill("dodge", (int)me->query_skill("dodge", 1) / 5);
                } else
                {
                        me->set("qi", 0);
                        return notify_fail("你太累了，还是休息一会儿吧。\n");
                }
	}
	return 1;
}


