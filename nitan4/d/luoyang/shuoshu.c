inherit ROOM;

void create()
{
	set("short", "˵�����");
        set("long", @LONG
�������˵�������һλ��ʮ����������������ڴ�����������
���ȣ�ҡͷ����˵����ͣ���������壬����������Ѧ�ٷ��ƣ������ƣ�
��Ӣ�ң����μǣ�ˮ䰴��ȵȣ���λ˵��������������ͨ����˵����
Һ��ɡ���Χ���������ǽ����ζ����ס�ĵ�ͷ�Ƶ���
LONG );
	set("no_clean_up", 0);
	set("exits", ([
  		"east" : __DIR__"chalou2",
	]));
        set("objects", ([
                "/d/beijing/npc/chaboshi" : 1,
                "/d/beijing/npc/teahuoji" : 1,
                "/d/beijing/npc/chake" : 4,
        ]));
	set("coor/x", -190);
	set("coor/y", 10);
	set("coor/z", 20);
	setup();
	replace_program(ROOM);
}