inherit ROOM;

void create()
{
	set("short", "��̨");
        set("long", @LONG
������ϷԺ�ĺ�̨���ط����󣬳��˻�ױ̨����û��ʲô�ˣ���
���������˷�װ�͵��ߣ��Եúܽ��գ����˶����ŵ�æµ�ţ���ױ��
��ױ��жױ��жױ���޵��ߵ��޵��ߣ�����װ������װ����Ҷ���Ϊ
ǰ̨�ı�������׼����
LONG );
	set("no_clean_up", 0);
	set("exits", ([
  		"west" : __DIR__"xiyuan",
	]));
        set("objects", ([
                "/d/beijing/npc/xizi1" : 2,
        ]));
	set("coor/x", -150);
	set("coor/y", -10);
	set("coor/z", 10);
	setup();
	replace_program(ROOM);
}