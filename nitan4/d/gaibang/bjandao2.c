// Room: /d/gaibang/bjandao2.c
// Date: Haa 96/03/22

#include <room.h>
inherit ROOM;

void create()
{
	set("short", "����");
        set("long", @LONG
����ؤ�Ｋ�����ܵĵ���ͨ��������ؤ�Ｘ����֮��Ѫ��ɡ�
LONG );
	set("exits", ([
		"north" : __DIR__"underbj",
		"south" : __DIR__"bjandao1",
	]));
	set("objects", ([
		CLASS_D("gaibang") + "/quan-gq" : 1,
	]));
	setup();
	replace_program(ROOM);
}
