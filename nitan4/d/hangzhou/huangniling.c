// huangniling.c
// Date: Nov.1997 by Venus
#include <room.h>
inherit ROOM;
void create()
{
        set("short", "������");
        set("long", @LONG
һ������·�������������ܷǳ��İ�����ż���ſ���Щ���˴Ҵ�
�������ϱ��ֱ�����ɽ��·��
LONG );
        set("exits", ([
            "southdown"   : "/d/hangzhou/maojiabu",
            "northdown"   : "/d/hangzhou/road3",
        ]));
        set("outdoors", "hangzhou");
        set("no_clean_up", 0);
        setup();
	replace_program(ROOM);
}