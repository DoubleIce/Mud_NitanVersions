#include <ansi.h>
inherit ROOM;

void create()
{
        set("short", "���");
        set("long", @LONG
�����������������µ�����ϣ��������ٹ���Զ���͵��ɶ��ˣ�
����ʼ�����ն�������
LONG );
        set("exits", ([
                "west" :  __DIR__"shudao19",
                "eastdown" : __DIR__"shudao17",
        ]));
        
        set("no_clean_up", 0);
        set("outdoors", "chengdu");
        set("coor/x", -360);
	set("coor/y", -180);
	set("coor/z", 0);
	setup();
	replace_program(ROOM);
}
