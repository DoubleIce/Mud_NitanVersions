// Room: /d/xiangyang/bingying3.c
// Date: Jan. 8 1999 by Winder

inherit ROOM;

void create()
{
	set("short", "��Ӫ");
        set("long", @LONG
�����Ǳ�Ӫ���������鵽�����ǹٱ����е����佫��ָ�����ж�
�������еĶ������������е����š�����������Ϣ����ǽ��������˧��
������ɫ��Ѳ�������ܡ����������������ȫ���ɴ��۾������㡣
LONG );
	set("item_desc", ([
		"dong" : "\n",
	]));

	set("exits", ([
		"south" : "/d/xiangyang/westjie3",
	]));
	set("objects", ([
		"/d/xiangyang/npc/pian" : 1,
		"/d/xiangyang/npc/zuo"  : 1,
		"/d/xiangyang/npc/bing" : 2,
	]));
	set("coor/x", -330);
	set("coor/y", -70);
	set("coor/z", 0);
	setup();
	replace_program(ROOM);
}
