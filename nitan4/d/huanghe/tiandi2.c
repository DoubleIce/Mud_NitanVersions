inherit ROOM;

void create()
{
	set("short", "���");
        set("long", @LONG
������ľ����ϡ�裬��Զ����Щ��ׯ�������������𡣴�ׯ��Χ
��һ������أ�������һЩ���ڸ�����ũ�ˡ�
LONG );
	set("exits", ([
		"southwest" : __DIR__"shulin5",
		"east"      : __DIR__"tiandi1",
	]));
	set("outdoors", "huanghe");
	set("coor/x", -40);
	set("coor/y", 60);
	set("coor/z", 0);
	setup();
	replace_program(ROOM);
}

