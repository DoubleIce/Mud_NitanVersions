#include <ansi.h>
inherit ROOM;

void create()
{
        set("short", "ף�ڷ�");
        set("long", @LONG
ף�ڷ�֮��Ϊ��ɽ���ľ�֮�ס��ڴ˸��Ⱥ�壬�����۵ס�����
�潭���ϼ����룬���ͥ������ѩɽ���Ƴ��Ÿ�����ʫ���С�[1��37mף��
����𣬷��εͰ�[2��37��0m��������ʫ�˺������ԡ�[1��37mף�����ɰε�������
����������[2��37��0m��������ߡ�
LONG );
        set("exits", ([
                "eastdown"   : __DIR__"shanlu004",
        ]));

        set("objects", ([
                CLASS_D("henshan") + "/mo" : 1,
        ]));    

        set("no_clean_up", 0);

        set("coor/x", -70);
	set("coor/y", 100);
	set("coor/z", 70);
	setup();
        replace_program(ROOM);
}

