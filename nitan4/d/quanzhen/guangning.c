#include <ansi.h>
inherit ROOM;

void create()
{
        set("short", "������");
        set("long", @LONG
������ȫ������֮���´�ͨ�����ң����Һ�С������һ��С����
һ��С�輸����û��ʲô��İ��衣�輸��ө͸������ϸһ����ԭ��
�����������������ĥ�ɵġ��輸�ϰڷ��ż�������������飬����
һЩ�����õĽ�Ǯ��
LONG );
        set("exits", ([
                "north" : __DIR__"piandian",
        ]));

        set("objects", ([
                CLASS_D("quanzhen") + "/hao" : 1,
        ]));
        setup();
        replace_program(ROOM);
}