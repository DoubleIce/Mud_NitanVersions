inherit ROOM;

void create()
{
	set("short", "����̲");
        set("long", @LONG
��������������������Ļ���̲�������ǻƺӱߵ�һ��Ƭˮ����
��أ��ƺ�ˮ���ĺ���ȥ�γ���һ��Ƭ����ˮ̲������ˮ�ݷ�ʢ����
�����������˴���������Ұ��������������ˮ��Ϸ��������Ϣ����
Ϊ����һ�󾰹ۡ�
LONG );
	set("exits", ([
		"north"     : __DIR__"nanmen",
		"southwest" : __DIR__"xiaoba",
	]));
	set("no_clean_up", 0);
	set("objects", ([
		"/clone/quarry/yang3" : 1,
                __DIR__"npc/sheep" : 2,
	]));
	set("outdoors", "lingzhou");
	setup();
	replace_program(ROOM);
}
