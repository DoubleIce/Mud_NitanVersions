// wuchang2.c

inherit ROOM;

void create()
{
	set("short", "���䳡");
        set("long", @LONG
����һ���ȱ����Ϊ��������䳡��������ִ�̽���������Ů��
������������ͬ�ڱ��������������ߺ��٣���������һЩ��������
��ϰ�书����һЩ��������˽���֪���ڸ�Щʲô��һֱ���ߴ�
Խ�����������͵������ˡ�
LONG );
	set("exits", ([
		"north" : __DIR__"wuchang",
                "east" : __DIR__"liangongfang",
	]));
	set("objects", ([
                "/clone/npc/mu-ren": 4,
	]));
        setup();
	replace_program(ROOM);
}