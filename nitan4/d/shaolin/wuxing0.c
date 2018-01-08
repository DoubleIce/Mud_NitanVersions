// Room: /d/shaolin/wuxing0.c
// Date: YZC 96/02/06

#include <ansi.h>

inherit ROOM;

string* dirs = ({"east", "south", "west", "north"});

void create()
{
	set("short",HIY "���ж�" NOR);
        set("long", @LONG
[1��33m�������ж�������һƬ�������ģ�����ϸ����ȴ�����������ĵ�
���ǽ�ϣ����ϣ����ϣ�����˷�������������Բ�����ͻ��Լ�ײ
��������ȥ������ѣĿ�������Ǻ��⡣����Ѫ���ܵĶ�֫�к�����
�����ϣ������Ѿ���Щʱ���ˡ�ǽ�ںں����ģ����Ǹ������ɡ�[2��37��0m
LONG );
	set("exits", ([
		"east" : __DIR__"wuxing4",
		"south" : __DIR__"wuxing3",
		"west" : __DIR__"wuxing1",
		"north" : __DIR__"wuxing2",
	]));
	set("no_clean_up", 0);
	setup();
}

int check_out(object me)
{
	int metal, wood, water, fire, earth;

	metal = me->query_temp("wuxing/��");
	wood = me->query_temp("wuxing/ľ");
	water = me->query_temp("wuxing/ˮ");
	fire = me->query_temp("wuxing/��");
	earth = me->query_temp("wuxing/��");

	if ( metal > 0 &&
		metal == wood && metal == water &&
		metal == fire && metal == earth )
	{
		me->delete_temp("wuxing");
		me->move(__DIR__"andao2");
                return 1;
	}
        return 0;
}

int valid_leave(object me, string dir)
{
	int count;

	if (member_array(dir, dirs) != -1)
	{
		if (dir == "north")
		{
//			write("*����ˮ*\n");
			count = me->query_temp("wuxing/ˮ");
			count++;
			me->set_temp("wuxing/ˮ", count);
			if (check_out(me))
                        {
                                write("��˳�����߳��������Թ���\n");
                                return 1;
                        }
		}
		else if (dir == "west")
		{
//			write("*���ľ*\n");
			me->delete_temp("wuxing");
			me->move(__DIR__"jianyu1");
                        write("��������أ�����ɮ�ࡣ\n");
                        return 1;
		}
	}
	return ::valid_leave(me, dir);
}

