// Room: /d/xiangyang/guofugate.c
// Date: Jan. 8 1999 by Winder

inherit ROOM;
#include <ansi.h>;
void create()
{
	set("short", "��������");
        set("long", @LONG
һ���������ӵĴ�լԺ�����������ǰ��ֻ����¥������������
������[1��32m                     ��   ��[2��37��0mȫ��̵ڶ�������Ү����ͼ�
���Ҷ�վ����ǰ�Ӵ�ǰ�����������ĸ�����ʿ��
LONG );
        set("outdoors", "xiangyang");
	set("exits", ([
		"south" : "/d/xiangyang/westjie1",
		"north" : "/d/xiangyang/guofuyuan",
	]));
	set("objects", ([
		"/d/xiangyang/npc/yelvqi" : 1,
		"/d/xiangyang/npc/jiading" : 2,
	]));
	set("coor/x", -300);
	set("coor/y", -80);
	set("coor/z", 0);
	setup();
	replace_program(ROOM);
}

