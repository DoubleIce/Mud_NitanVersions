//JMQSHULIN6.C

inherit ROOM;

void create()
{
	set("short", "��ľ������");
        set("long", @LONG
����ǰ��Ȼһ���������У�ֻ������ǰ�󣬵�����������ǵص�
��֪���ľ����������ɰأ�������ɼ������һ����ʵ��֦Ҷ��һ��
���ɡ��������գ�������ա����ƺ���ʧ�˷�����ûͷ��Ӭ�㵽
���Ҵ���
LONG );
	set("exits", ([
		"east" : __DIR__"jmqshulin6",
		"west" :__DIR__"jmqjiguan",
                    "north" : __DIR__"jmqshulin4",
		"south" : __DIR__"jmqshulin6",
	]));
        set("objects", ([
                __DIR__"obj/pine" : random(5),
        ]));
	set("outdoors", "mingjiao");
	set("no_clean_up", 0);
	setup();
	replace_program(ROOM);
}