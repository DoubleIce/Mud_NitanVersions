inherit ROOM;

void create()
{
	set("short", "����ɽ·");
        set("long", @LONG
���н���������һ������һ�죬����������������ǿ����;����
��ʲôǿ����ֻ�ǻ�ɳ���棬����͸�ǣ�ȴҲ��ʵ�Ѱ���
LONG );
        set("exits",([
		"westup" : __DIR__"shanlu2",
		"east" : __DIR__"shanlu",
	]));
        set("objects", ([
                __DIR__"npc/seller" : 1,
        ]));
	set("outdoors", "kunlun");
	setup();
	replace_program(ROOM);
}
