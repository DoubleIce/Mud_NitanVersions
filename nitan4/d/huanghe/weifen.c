#include <room.h>

inherit ROOM;
void create()
{
        set("short", "μ������");
        set("long", @LONG
�ںӺ�μ�ӻ���ƺӣ���������ˮ�ƣ�Ҳ�����˸������ɳ����
��Ӷ��ǽ����������¡�
LONG );
        set("exits", ([
                "south" : __DIR__"huanghe1",
                "north" : __DIR__"huanghe_1",
                "southwest" : "/d/heimuya/road5",
        ]));
        set("no_clean_up", 0);
        set("outdoors", "huanghe");
        set("coor/x", -10);
	set("coor/y", 90);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}

