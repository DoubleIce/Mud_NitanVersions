// Room: /d/fuzhou/fzroad3.c
// Date: May 12, 98  Java

inherit ROOM;

void create()
{
	set("short", "����ŵ�");
        set("long", @LONG
�Թ������޳�;����������ȫ����������������������������ͨ��
�ŵ��ųơ���ǧ�˰ٿ������������ߣ���ʯ���ͣ�����ͷ����̡���
�����ף�������ƽ�����ˡ�
LONG );
	set("exits", ([
		"northdown" : __DIR__"fzroad2",
		"southdown" : __DIR__"yanping",
	]));
        set("objects", ([
		"/d/taishan/npc/tiao-fu" : 2,
	]));
	set("outdoors", "fuzhou");
	set("coor/x", 80);
	set("coor/y", -80);
	set("coor/z", 10);
	setup();
	replace_program(ROOM);
}
