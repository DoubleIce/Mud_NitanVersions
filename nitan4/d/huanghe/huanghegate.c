// Room: /huanghe/huanghegate.c
// Java. Sep 21 1998

#include <room.h>

inherit ROOM;
void create()
{
	set("short", "�ƺӰ�կ��");
        set("long", @LONG
����һ������׳�۵�կ�ţ����и߹���һ���д�š��ƺӰ�
���������֡�կ�����ĸ߹ң���ģ��С���ƺӰ��ǻƺ��ذ���һ����
��ᣬƽ�շ�����裬��ѹ���գ������ˡ�����ɳͨ���书��տ��
�����������������̺��������˵ȸ��ֽύ��������ƺƴ󡣾�����
����˹��ᣬ������������
LONG );
	set("exits", ([
		"east"  : __DIR__"huanghe1",
		"west"  : __DIR__"guangchang",
	]));
	set("objects", ([
		__DIR__"npc/ma" : 1,
		__DIR__"npc/shen" : 1,
	]));
//	set("no_clean_up", 0);
	set("outdoors", "huanghe");
	set("coor/x", -20);
	set("coor/y", 80);
	set("coor/z", 0);
	setup();
	replace_program(ROOM);
}
