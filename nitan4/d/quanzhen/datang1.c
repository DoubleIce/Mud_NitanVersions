#include <ansi.h>
#include <room.h>
inherit ROOM;

void create()
{
        set("short", "����һ��");
        set("long", @LONG
�����Ǵ��ã���ȫ��̽Ӵ����˵ĵط����úܴ󣬼�ʮ������һ
���ſ�Ҳ˿������ӵ�������������������ש��������ͯ��æǰæ��
�ض˲���ˮ�к����ˡ�
LONG );
        set("exits", ([
                "east" : __DIR__"datang2",
                "west" : __DIR__"damen",
                "north" : __DIR__"huizhentang",
                "south" : __DIR__"xianzhentang",
        ]));
        set("objects",([
                __DIR__"npc/daotong" : 1 + random(3),
        ]));
        create_door("west", YEL "��ͭ����" NOR, "east", DOOR_CLOSED);
        set("valid_startroom", 1);
        setup();
        "/clone/board/quanzhen_b"->foo();
}