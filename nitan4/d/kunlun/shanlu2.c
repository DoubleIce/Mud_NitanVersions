inherit ROOM;

void create()
{
	set("short", "����ɽ·");
        set("long", @LONG
���н���������һ������һ�죬����������������ǿ����;����
��ʲôǿ����ֻ�ǻ�ɳ���棬����͸�ǣ�ȴҲ��ʵ�Ѱ���
LONG );
        set("exits",([
		"eastdown" : __DIR__"shanlu1",
		"southup" : __DIR__"bayankala",
	]));

	set("outdoors", "kunlun");
	setup();
	replace_program(ROOM);
}
