// Room: /d/fuzhou/xidajie.c
// may. 12 1998 Java

inherit ROOM;

void create()
{
	set("short", "�����");
        set("long", @LONG
��ֱ��棬һ���ṹ��ΰ�Ľ���ǰ������ʯ̳�ϸ�����һ������
��ߵ���ˣ���������Ʈ����������ý�������һͷ������צ��ʨ
�ӣ������չ��������������ʨ��ͷ��һ�Ժ�˿���������չ����衣
����������д�š������ھ֡��ĸ����֣������������վ��Ƿ���
LONG );

	set("exits", ([
		"southup" : __DIR__"wushan",
		"north"   : __DIR__"biaoju",
		"east"    : __DIR__"dongjiekou",
		"west"    : __DIR__"ximendajie",
	]));
	set("outdoors", "fuzhou");
	set("coor/x", 140);
	set("coor/y", -110);
	set("coor/z", 0);
	setup();
	replace_program(ROOM);
}
