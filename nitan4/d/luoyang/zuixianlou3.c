inherit ROOM;

void create()
{
	set("short", "����¥����");
        set("long", @LONG
����������������ѧʿ������������ʫ��������������Ҳ������
�߳Ժȱ������ס�����Ҳ�ǳ���ٰ�ϲ�����ѳ�������վ��¥����
����ֻ�����Ŀ�������������һ�غ�ˮ���̲��������������ǳ�ɽ��
�룬�����ۻ룬Ρ��׳�ۡ�
LONG );

	set("no_clean_up", 0);
	set("exits", ([
  		"up" : __DIR__"zuixianlou4",
  		"down" : __DIR__"zuixianlou2",
	]));
        set("objects", ([
                "/d/zhongzhou/npc/fushang" : 2,
        ]));
	set("coor/x", -160);
	set("coor/y", 10);
	set("coor/z", 30);
	setup();
	replace_program(ROOM);
}