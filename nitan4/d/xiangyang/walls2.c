// Room: /d/xiangyang/walls2.c
// Date: Jan. 8 1999 by Winder

inherit ROOM;

void create()
{
	set("short", "ʯ��");
        set("long", @LONG
���ǵ����ͷ��ʯ�ף���Ϊ��ǽ�ܸߣ����Ժܶ���ʯ�������п�
���������µ�б�µ���
LONG );
        set("outdoors", "xiangyang");
	set("no_clean_up", 0);

	set("exits", ([
		"eastup"   : "/d/xiangyang/walls4",
		"westdown" : "/d/xiangyang/southgate1",
	]));
	set("coor/x", -290);
	set("coor/y", -140);
	set("coor/z", 10);
	setup();
}
int valid_leave(object me, string dir)
{
        int c_skill;
        mixed c_exp;
	if (dir == "eastup" )
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
                        return notify_fail("��̫���ˣ�������Ϣһ����ɡ�\n");
                }
	}
	return 1;
}

