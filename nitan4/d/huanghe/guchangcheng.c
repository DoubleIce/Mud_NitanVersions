#include <ansi.h>
#include <room.h>
inherit RIVER;

void create()
{
	set("short", "�ų���");
        set("long", @LONG
������һ�ιų��ǡ��ഫ�ǵ�����ʼ���������ĸ�������������
ʮ�������ޡ����±�Ǩ���׺�ɣ������������Ƭ���棬Ψһ��
ϡ�ɼ����Ǻ����Ƴɵķ��̨���С����һ������������ƺӴ���
����ȥ������(river)��һҶС�ۡ�
LONG );
        set("arrive_room", "/d/lingzhou/xuanhebao");
	set("exits", ([
		"southwest" : __DIR__"yinpanshui",
		"southeast" : __DIR__"shimen",
	]));
	set("objects", ([
		__DIR__"npc/menmian" :1,
	]));

        set("resource/fish", ({ "/clone/fish/liyu",
                                "/clone/fish/jiyu",
                                "/clone/fish/qingyu",
                                "/clone/fish/caoyu", }));

	set("outdoors", "huanghe");
	set("coor/x", -20);
	set("coor/y", 170);
	set("coor/z", 0);
	setup();
        replace_program(RIVER);
}