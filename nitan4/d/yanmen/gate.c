#include <ansi.h>
inherit ROOM;

void create()
{
        set("short", "���Ź�"NOR);
        set("long", @LONG
������ǡ����Ρ���Ӫ�ˣ�һ�����߸�������������һ����
������顸�Ρ��֣�ǰ�治Զ�����ξ�Ԫ˧����Ӫ�ˡ�����פ�ص���
����Ϊ����ֹ�ɹ��������ֵĹؼ����ϣ�һ�����ﱻ�������ƣ���ô
���ξ��᧿�Σ�ˣ�
LONG );

        set("no_fly", "1");
        set("exits", ([ /* sizeof() == 5 */
              "south" :   "d/guanwai/laolongtou",
               "north" :   __DIR__"shance",
        ]));

        set("objects", ([

        ]));

        setup();
        replace_program(ROOM);
}


