inherit ROOM;

void create()
{
	set("short", "���");
        set("long", @LONG
������һ��Ƭũ���Զ����Щ��ׯ�������������𡣴�ׯ��Χ
��һ������أ�������һЩ���ڸ�����ũ�ˡ����ﲻʱ����һ����
��Ȯ�͡�
LONG );
	set("exits", ([
		"southwest" : __DIR__"tiandi3",
		"north"     : __DIR__"huanghe1",
	]));
	set("objects", ([
		"/clone/quarry/gou" : 1,
	]));
	set("no_clean_up", 0);
	set("outdoors", "huanghe");
	set("coor/x", -10);
	set("coor/y", 70);
	set("coor/z", 0);
	setup();
	replace_program(ROOM);
}

