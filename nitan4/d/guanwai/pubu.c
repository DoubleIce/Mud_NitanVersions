// /guanwai/pubu.c

inherit ROOM;

void create()
{
	set("short", "�����ٲ�");
        set("long", @LONG
���ˮ��������߸߷������䣬����֮��Զ�����ˮ��ֱ���
�ֹȣ�����Ȼ������ڡ������ӳ��ǡ�ư������գ�ˮ�����������
�ȵף������ɸߵķ��ˣ�������Ůɢ�������������£�����Ծ��
譲�׳��֮��������ʫ�ƣ����׺����������ģ���ˮ�������������
����������ѩ����ͬ��ʹҷ����������ʯ�ɲ׺���ֱ�ɳ���ʶ�ţ��
��ʶ��Ȫ����Ȥ��������������Ρ���
LONG );
	set("exits", ([
		"southeast"  : __DIR__"damen",
		"westdown"   : __DIR__"xiaotianchi",
	]));
	set("no_clean_up", 0);
	set("outdoors", "guanwai");
	setup();
	replace_program(ROOM);
}
