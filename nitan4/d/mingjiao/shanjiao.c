// Room: /d/mingjiao/shanjiao.c
// Date: Java 97/05/11

#include <room.h>
inherit ROOM;

void create()
{
    set("short", "����ɽ��");
        set("long", @LONG
������ǧ�����صĶ�´��Զ������ƺƣ��������ơ�������Ұǧ
����������������ɽΡΡ���������߳�����ְ˰�������̾�
��������Ⱥɽ֮�С�����----�Ƕ������ֺ����������ĵط��������
���������������ĺ��ֵܣ�����������а��������������Ⱥɽ֮��
�ȴ�����ȥ��д��һ�����ִ��档
LONG );
    set("exits", ([
        "west" : __DIR__"tomen2",
        "east" : __DIR__"gebitan5",
        "westup" : "/d/kunlun/zhenyuanqiao",
    ]));
        set("objects", ([
                "/d/mingjiao/npc/monkey" : 2,
        ]));

    set("outdoors", "mingjiao");
    set("no_clean_up", 0);
    setup();
    replace_program(ROOM);
}
