inherit ROOM;

void create()
{
	set("short", "����");
        set("long", @LONG
��������߰�����ֻ������ͷ������һЩ�����������ż����ï
�ܵ�Ҷ��͸����һ�߹������Ҷ�ڷ��衣��ľ���õ���ζ�����ᴫ��
Ұ�޵�Х��ʹ�˲�����ԥ��ǰ���ĽŲ���
LONG );
	set("exits", ([
		"northwest" : __DIR__"shulin5",
		"east"      : __DIR__"shulin3",
		"south"     : __DIR__"shulin2",
	]));
        set("quarrys", ([
                "tu"        : 100000,
                "ji"        : 80000,
                "pao"       : 50000,
                "caihuashe" : 50000,
                "dushe"     : 20000,
                "hu"        : 5000,
                "bao"       : 2000,
                "laohu"     : 2000,
        ]));
	set("outdoors", "huanghe");
	set("coor/x", -40);
	set("coor/y", 40);
	set("coor/z", 0);
	setup();
	replace_program(ROOM);
}

