// Room: /huanghe/jingyuan.c
// Java Sep. 22 1998

#include <room.h>

inherit ROOM;

void create()
{
	set("short", "��Զ");
        set("long", @LONG
��Զ�Ǹ�����С�ĳ��򣬻�ɳ�������ʮ��ĵط���һ���ŵ�
�������������ס�ˡ������������һ��ϴ�����ޣ��ۼ��˲��ٴ�
������������Щ�����˵�ǵ����Ƴ��������ͻ�ʺ���������
��ʱ���֡���Ҳ�Ǿ�Զ���������������߲�Զ���ǻƺӣ�������һ��
ƬɳĮ��
LONG );
	set("exits", ([
		"north"     : __DIR__"hongshanxia",
		"south"     : __DIR__"shamo",
	]));
	set("no_clean_up", 0);
	set("outdoors", "huanghe");
	set("coor/x", -10);
	set("coor/y", 140);
	set("coor/z", 0);
	setup();
	replace_program(ROOM);
}

