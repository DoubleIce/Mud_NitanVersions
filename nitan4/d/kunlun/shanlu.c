inherit ROOM;

void create()
{
        set("short", "����ɽ·");
        set("long", @LONG
���н���������һ������һ�죬����������������ǿ����;����
��ʲôǿ����ֻ�ǻ�ɳ���棬����͸�ǣ�ȴҲ��ʵ�Ѱ���
LONG );
        set("exits",([
		"west" : __DIR__"shanlu1",
		"east" : __DIR__"zhenyuanqiao",
	]));

	set("outdoors", "kunlun");
	setup();
	replace_program(ROOM);
}
