#include <ansi.h>
inherit ROOM;

void create()
{
        set("short", "����Ͽ");
        set("long", @LONG
������ǳ�����Ͽ������Ͽ������������ɽ������������գ���
��ν��Գ���ĩ�ʰ�����������ӵ��Ƚ�խ����ˮ��Ĳ�����������
����������������ʱ��������������ȥ��
LONG );
        set("exits", ([
  		"west" : __DIR__"sanxia2",
  		"east" : __DIR__"shudao10",
        ]));
        set("no_clean_up", 0);
        set("outdoors", "chengdu");
        set("coor/x", -260);
	set("coor/y", -180);
	set("coor/z", -40);
	setup();
        replace_program(ROOM);
}
