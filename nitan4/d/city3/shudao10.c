#include <ansi.h>
inherit ROOM;

void create()
{
        set("short", "ʯ��");
        set("long", @LONG
һ��Сʯ�ף��е��������ã���ݴ�ʯͷ�ķ�϶�г��˳�������
Щ�ط���ʯ�����������Զ���Ѿ�ĥ�Ĺ⻬�羵�����Ͽ�ȥ��ֻ����
�����м������ӡ�
LONG );
        set("exits", ([
                "east" :  __DIR__"baidicheng",
                "west" : __DIR__"sanxia1",
        ]));
        set("objects", ([
                "/d/beijing/npc/old2" : 1,
        ]));
        set("no_clean_up", 0);
        set("outdoors", "chengdu");

        set("coor/x", -250);
	set("coor/y", -180);
	set("coor/z", -40);
	setup();
        replace_program(ROOM);
}
