// Room: /d/fuzhou/wuyishan7.c
// Date: May 12, 98  Java

inherit ROOM;

void create()
{
	set("short", "��Ů��");
        set("long", @LONG
��Ů��ͤͤ����Ů������ͻأͦ�Ρ��嶥���ܲδأ�ǡ��ɽ����
�ޡ��ұ�����⻬������������������Ϫ�ϣ���Ȼ�����ַ�����·
�ʵǡ����廨��ˮһ��壬��Ǳ�����Ů�ݡ�����д�ա�����ԡ��̶��
Ϊ��Ů��ԡ�����嶫Բʯ�羵����Ϊ��ױ̨��
LONG );
	set("exits", ([
		"north" : __DIR__"wuyishan2",
	]));
	set("outdoors", "fuzhou");
	set("coor/x", 60);
	set("coor/y", -80);
	set("coor/z", 0);
	setup();
	replace_program(ROOM);
}

