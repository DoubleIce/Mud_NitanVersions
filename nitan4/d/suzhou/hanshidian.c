// Room: /d/suzhou/hanshidian.c
// Date: May 31, 98  Java

inherit ROOM;

void create()
{
	set("short", "��ʰ��");
        set("long", @LONG
���﹩�����ഫΪ���ͺ϶��ɡ������ĺ�ɽ��ʰ�ý���������
̬����������ϲ������ɽ��ÿ���Ϧ��ҹ��ײ��һ������죬�京��
�ǳ���ӭ�ºͼ������һ�����λ��ɮ��
LONG );
	set("no_clean_up", 0);
	set("exits", ([
		"out"   : "/d/suzhou/fengqiao",
		"west"  : "/d/suzhou/zhengdian",
	]));
	set("coor/x", 140);
	set("coor/y", -200);
	set("coor/z", 0);
	setup();
	replace_program(ROOM);
}
