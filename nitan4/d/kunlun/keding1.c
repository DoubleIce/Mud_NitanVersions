inherit ROOM;

void create()
{
	set("short", "����");
        set("long", @LONG
�����ǿ���������򵥣�ֻ��һЩ���Ӻ����ӣ������ϰ���д��
�͵��Ĺ�����ʳ�á����ٵĽ�����ʿ��Զǧ���������������ȵ�����
ЪϢƬ�̣��ָ�һ�¡�
LONG );
        set("exits",([
		"west" : __DIR__"elang01",
	]));

	set("outdoors", "kunlun");
	setup();
	replace_program(ROOM);
}
