// Room: /city/kedian2.c
// Java Sep. 21 1998
inherit ROOM;

void create()
{
	set("short", "�͵��¥");
        set("long", @LONG
�������ڿ͵��¥�������ϣ����������ӿͷ��ﲻʱ�غ����Ĵ�
������һ��߹�һ�󡣲�ʱ��˯�����ʵ��ÿͽ�����������¥�µ���
�񴦸���Ǯ������˯����
LONG );
	set("exits", ([
		"down"  : __DIR__"kedian",
		"enter" : __DIR__"kedian3",
	]));
	set("no_clean_up", 0);
	set("coor/x", -70);
	set("coor/y", 80);
	set("coor/z", 10);
	setup();
	replace_program(ROOM);
}
