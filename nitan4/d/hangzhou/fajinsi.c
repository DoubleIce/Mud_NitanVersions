// fajinsi.c
// Date: Nov.1997 by Venus
#include <room.h>
inherit ROOM;
void create()
{
        set("short", "������");
        set("long", @LONG
��������ɽ��������ǰСϪ��ˮ��������οͲ�ʱ�Ľ���������
�����������á���������ɽ��·��
LONG );
        set("exits", ([
                "southup"   : "/d/hangzhou/shanlu3",
                "northdown" : "/d/hangzhou/shanlu2",
        ]));
        set("objects", ([
           "/d/hangzhou/npc/shami" : 1,
           "/d/hangzhou/npc/guest" : 1,
        ]));
//        set("no_clean_up", 0);
        set("outdoors", "hangzhou");
        setup();
        replace_program(ROOM);
}