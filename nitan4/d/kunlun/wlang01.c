inherit ROOM;

void create()
{
	set("short", "����");
        set("long", @LONG
����һ�����ȣ�����ǰ���Ϳͷ������Ͽ������ִ��Ľ�����ʿ
�߹����������⣬��һƬ��ɫ�����֣��ľ����£�ֻ�������ϴ�����
��������
LONG );
        set("exits",([
		"east" : __DIR__"qianting",
		"west" : __DIR__"keting2",
	]));

	set("outdoors", "kunlun");
	setup();
	replace_program(ROOM);
}
