inherit ROOM;

void create()
{
	set("short", "�ͷ�");
        set("long", @LONG
�����ǹ��������ǵ�ס�������������һ��ƽ�����ŵ���������
����һ�Ŵ������ϵı��챻�����������롣��ͷ���Եĵط�����һ��
���ӣ��Ա߻�����һ�����ӡ���������ط����ķ��ı����Ա߻�����
�����顣���ϰ���һ��ĵ������һ˿�������Ʒ��С���Ϊ�����ǵ���
�Ĵ�Ӣ�ۣ����Խ������в��ٺ���ÿ�궼���ݷ�����
LONG );
        set("no_fight", 1);
	set("no_clean_up", 0);
	set("sleep_room", 1);
	set("exits", ([
		"east" : __DIR__"guofu_huayuan",
	]));
	setup();
	replace_program(ROOM);
}
