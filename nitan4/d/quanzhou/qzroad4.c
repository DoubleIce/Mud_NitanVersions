// Room: /d/quanzhou/qzroad4.c
// Date: May 7, 96   Jay

inherit ROOM;

void create()
{
	set("short", "ɽ·");
        set("long", @LONG
������һ��ɽ·�ϡ�ʱֵ���գ�·�Ե�ɽ���Ͽ����˽��ɫ����
�˻��������ǽ������Ǽ��ˡ���������븣������ɽ����������һ��
��·����Ϣ��С��ͤ��
LONG );
	set("exits", ([
                "north"   : __DIR__"jxnanmen",
                "west"    : __DIR__"qzroad3",
//		"southup" : __DIR__"qzroad5",
		"southup" : "/d/fuzhou/fzroad1",
		"east"    : __DIR__"chating",
	]));
	set("no_clean_up", 0);
	set("outdoors", "quanzhou");
	set("coor/x", 80);
	set("coor/y", -40);
	set("coor/z", 0);
	setup();
	replace_program(ROOM);
}
