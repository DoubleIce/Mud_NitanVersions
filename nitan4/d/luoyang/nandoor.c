inherit ROOM;

void create()
{
	set("short", "�ڳ�����");
        set("long", @LONG
�����ڳ����Ÿ����ɣ���Լ�������࣬������ĳ�����������ȭ
ͷ���С���������Ŷ���Լ���ɣ���Լÿ������ʱ���ͻ��ٱ����ء�
��������������׽��֮��Ĺٸ�ͨ����һ����ֱ����ʯ�������ϱ�
�������죬��ȥ���������ڳ��ˣ�����һ��������ɽ´��������Ұ��
LONG );
        set("outdoors", "luoyang");
        set("no_clean_up", 0);
        set("exits", ([
  		"north" : __DIR__"sroad7",
  		"south" : __DIR__"guandaos1",
		"east" : __DIR__"suishi6",
  		"west" : __DIR__"suishi7",
	]));
        set("objects", ([
                "/d/kaifeng/npc/guanbing" : 4,
                "/d/beijing/npc/ducha" : 1,
                "/clone/npc/walker" : 1,
        ]));

	set("coor/x", -170);
	set("coor/y", -50);
	set("coor/z", 10);
	setup();
	replace_program(ROOM);
}