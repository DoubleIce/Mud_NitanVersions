#include <ansi.h>
#include <room.h>

inherit ROOM;

void create()
{
        set("short", "�㳡");
        set("long", @LONG
������һ��ƽƽ�����Ĵ�㳡���㳡���������ɵĵ�����ϰ�䣬
ǰ�治Զ����һ���޴��ʯ���磬������������ɵ�ǰ���ˣ������
������Ȼ�ǹ㳡��
LONG );
        set("exits",([
                "north" : __DIR__"shanlu04",
                "south" : __DIR__"pingfeng",
                "west" : __DIR__"guangchangw",
                "east" : __DIR__"guangchange",
        ]));

        set("objects",([
                CLASS_D("kunlun") + "/gaozecheng" : 1,
                __DIR__"npc/kl-dizi2" :  2,
        ]));
        set("outdoors", "kunlun");
        setup();
        replace_program(ROOM);
}
