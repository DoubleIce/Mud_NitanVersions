// Room: /d/fuzhou/fzroad1.c
// Date: May 12, 98  Java

inherit ROOM;

void create()
{
	set("short", "إ����");
        set("long", @LONG
إ���̸߾���ϼ���ϣ�����Ⱥɽ���࣬������ڣ�ʮ��ˬ������
���Ǹ���С��С���䣬��Ȼ���������Ŀ��̷��࣬����Ҳֻ��һ��С
С�͵ꡣ
LONG );
	set("exits", ([
		"north"     : __DIR__"fzroad1",
		"southdown" : __DIR__"fzroad2",
		"west"      : __DIR__"kedian",
	]));
        set("objects", ([
		"/d/huashan/npc/haoke" : 2,
	]));
	set("outdoors", "fuzhou");
	set("coor/x", 80);
	set("coor/y", -60);
	set("coor/z", 10);
	setup();
	replace_program(ROOM);
}
