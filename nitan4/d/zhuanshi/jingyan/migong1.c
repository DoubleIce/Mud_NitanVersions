#include <ansi.h>
inherit ROOM;

void create()
{
	set("short", WHT"���㹬����"NOR);
        set("long", @LONG
ͻȻ����ǰһ����һ���޴�Ĺ������������ǰ�������Ǵ�˵��
�ľ��㹬�����㹬ռ�ؼ��㣬���̨ͤ������ɭȻ��ȫ����ɽ������
��������壬�����й�����֮���ɣ����㹬������ǧ�����ɽ���£�
Ψһ;����һ��ֱͨ���ŵĴ�ʯ�ţ�ʯ�ſ�㣬���������ۣ���
�񹤣����ư��磬ʹ������һ�򵱹����Ī�еĸ�̾��
LONG );

        set("outdoors", "qianhuigu");
              set("no_stab", 1); 
        set("exits", ([ /* sizeof() == 3 */
                "north" : __DIR__"migong2",
        ]));

        setup();
        replace_program(ROOM);
}

