//ROOM damen.c
inherit ROOM;
void create()
{
	set("short", "�ƻ�������");
        set("long", @LONG
�����ͨ���ƻ������Ĵ��š��������Ҹ���һƬ�ʻ�����ζϮ
�ˣ�ͨ�����ſ���ȥ������ܶ��ʻ���������̲�ס��Ҫ��ȥ������
LONG );
        set("outdoors", "yihua");
        set("exits", ([
		"north" : __DIR__"yihua_out",
		"south" : __DIR__"yihua_ge",
        ]));

	set("objects",([
                //__DIR__"npc/huanu" : 1,
	]));
	setup();
}

int valid_leave(object me, string dir)
{
	if (  (dir == "south")
           && ((string)me->query("family/family_name") != "�ƻ���")
	   && objectp(present("hua nu", environment(me))) )
	 return notify_fail
		("��ū������ס�㣬˵�������������ƻ����Ľ��أ���Ҫ�������ܣ���Ȼ��ȥ���߹�������\n");
	return ::valid_leave(me, dir);
}