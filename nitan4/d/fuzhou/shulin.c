// Room: /d/fuzhou/shulin.c
// Date: May 12, 98  Java

inherit ROOM;

void create()
{
	set("short", "����");
        set("long", @LONG
�����ڸ��ݶ����������С�����ʱʱ�����������������������
���ƺ���һС��������һɽ��������ġ�����ƽ̹ƽԭ�ϡ�
LONG );
	set("exits", ([
                "north"  : __DIR__"wuxiang",
                "eastup" : __DIR__"gushan",
                "west"   : __DIR__"dongmen",
	]));
	set("outdoors", "fuzhou");
	set("coor/x", 190);
	set("coor/y", -110);
	set("coor/z", 0);
	setup();
	replace_program(ROOM);
}
