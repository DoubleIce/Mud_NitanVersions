// Room: /d/quanzhou/nanhu.c
// Date: May 21, 96   Jay

inherit ROOM;

void create()
{
	set("short", "�����Ϻ�");
        set("long", @LONG
�����Ǽ����Ϻ����ڽ������Ҷ���У����ⱥʵ��һ��������
ת�ĸ�����Ʈ����ˮ���ɵĺ����ϡ�����һ��������һ������������
�Ѿá�
LONG );
	set("exits", ([
            "west"      : __DIR__"jiaxing",
            "east"      : __DIR__"jiaxinggang",
            "south"     : __DIR__"tieqiang",
            "southeast" : __DIR__ "nanhu1",
	]));

	set("outdoors", "jiaxing");

	set("coor/x", 90);
	set("coor/y", -20);
	set("coor/z", 0);
	setup();
	replace_program(ROOM);
}