inherit ROOM;

void create()
{
	set("short", "����");
        set("long", @LONG
����һ�����ȣ�������ʥ�úͻ�԰�����Ͽ������ִ��Ľ�����
ʿ�߹����������⣬��һƬ��ɫ�����֣��ľ����£�ֻ�������ϴ���
����������
LONG );
        set("exits",([
		"southup" : __DIR__"sanshengtang",
		"north" : __DIR__"huayuan1",
	]));

	set("outdoors", "kunlun");
	setup();
	replace_program(ROOM);
}
