inherit ROOM;

void create()
{
	set("short", "����ɽ���");
        set("long", @LONG
����λ����ɽ֮���һ��Сɽ�ڡ�ֻ������ɽ������ǧ�Ⱥɽ
������ɽ�ϵ���ľ�����࣬����ʱ¶����ͺͺ��ɽ���ʯͷ��ɽ����
�Ͼ�Ϊ��ѩ���ǣ��������ţ��߲�������
LONG );
	set("exits",([
		"west" : __DIR__"klshanlu",
		"southeast" : __DIR__"kekexili",
	]));

	set("outdoors", "kunlun");
	setup();
	replace_program(ROOM);
}
