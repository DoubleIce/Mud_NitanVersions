#include <ansi.h>
#include <room.h>

inherit ROOM;

void create()
{
	set("short", "������");
        set("long", @LONG
������ǰ���оŽ����������۵�������ˮ�档һ·����������
��ʯ��Ȫ���仨������ˮɫ���ܡ����ߴ�����������������������ʯ
Ϊ������¥��գ�ת�۴�����Сͤ��ӡ�
LONG );
	set("exits",([
		"northwest" : __DIR__"shanlin1",
		"southeast" : __DIR__"sanshengtang",
	]));
	setup();
	replace_program(ROOM);
}
