inherit ROOM;

void create()
{
	set("short", "����");
        set("long", @LONG
��������߰�����ֻ������ͷ���ϴ���Щ�����������ż����ï
�ܵ�Ҷ��͸����һ�߹������Ҷ�ڷ��衣��ľ���õ���ζ�����ᴫ��
Ұ�޵�Х��ʹ�˲�����ԥ��ǰ���ĽŲ���
LONG );
	set("exits", ([
		"west"      : __DIR__"shulin6",
		"southeast" : __DIR__"shulin4",
		"northeast" : __DIR__"tiandi2",
	]));
	set("objects", ([
		"/d/taishan/npc/tangzi" : 1,
	]));
	set("no_clean_up", 0);
	set("outdoors", "huanghe");
	set("coor/x", -50);
	set("coor/y", 50);
	set("coor/z", 0);
	setup();
	replace_program(ROOM);
}

