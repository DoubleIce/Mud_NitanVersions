inherit ROOM;

void create()
{
	set("short", "����·");
        set("long", @LONG
������·�������������һ����·���ֵ��������ɾ�����������
��·�汻��ˮ��ù����羵����·������߷��ߴ����ΰ����������
�޸�լԺ��˫�˺ϱ�������ʮ��һ�꣬������������ߡ�����������
���ڣ���������һ�����̡�
LONG );
        set("outdoors", "luoyang");
	set("no_clean_up", 0);
	set("exits", ([
  		"east" : __DIR__"yamendoor",
  		"north" : __DIR__"nroad3",
  		"south" : __DIR__"nroad1",
  		"west" : __DIR__"liangpu",
	]));
        set("objects", ([
                "/d/beijing/npc/boy1" : 1,
                "/d/beijing/npc/old2" : 1,
        ]));
	set("coor/x", -170);
	set("coor/y", 20);
	set("coor/z", 10);
	setup();
	replace_program(ROOM);
}