// Create by lonely@NT
inherit ROOM;
#include <ansi.h>;
void create()
{
        set("short", HIW"��ʯ·"NOR);
        set("long", @LONG
���������Źص���ʯ·���Ƕ����ϱ��Ľ�ͨ�ؾ�֮·������Ϊ��
�ұ���֮�أ���ɽ�����ƶ��£�ֻ��һ����խ����С������������
������ʯ�����󰵸�ɱ����
LONG );
        set("outdoors", "yanmen");
        set("exits", ([
                "north" :  __DIR__"luanshi3",
                "south" :  __DIR__"luanshi5",
        ]));
        set("no_fly",1);
        setup();
        replace_program(ROOM);
}