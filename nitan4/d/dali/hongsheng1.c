//Room: /d/dali/hongsheng1.c
//Date: June. 29 1998 by Java

inherit ROOM;
void create()
{
	set("short","塔基");
        set("long", @LONG
宏圣寺塔基座系用石板砌成，与千寻塔基为砖砌不同。基座西面
有塔门，可入内攀登而上。
LONG );
	set("exits",([ /* sizeof() == 1 */
	    "out"    : "/d/dali/hongsheng",
	    "up"     : "/d/dali/hongsheng2",
	]));
	set("no_clean_up", 0);
	setup();
}

int valid_leave(object me, string dir)
{
        string c_exp;
        int c_skill;
	if (dir == "up" )
	{
                c_exp   = me->query("combat_exp");
		c_skill = (int)me->query_skill("dodge",1);
                if (me->query("qi") > 20)
                {
        		me->receive_damage("qi", 20);
                        if (count_lt(count_div(count_mul(count_mul(c_skill, c_skill), c_skill), 10), c_exp) &&
                            c_skill < 101)
        		me->improve_skill("dodge", (int)me->query_skill("dodge", 1) / 5);
        		tell_object(me,"你爬上一层楼，有些累了。\n");
                } else
                {
                        me->set("qi", 0);
        		tell_object(me,"你是在爬不动了。\n");
                        return 0;
                }
	}
	return 1;
}
