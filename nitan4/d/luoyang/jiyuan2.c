inherit ROOM;

void create()
{
	set("short", "ӭ�ʹ���");
        set("long", @LONG
��վ�ڴ���¥��¥��ӭ�ʹ�����������������첻�����ơ���
�õľ��Ծ��µĴ��ϵ��£�ͻȻ�������Ī�����ջ�ͳ嶯��������
�������ǧ�������ڵ������㣬���м���ɧ��ʮ����Ѿ����������
���ԣ����ֹ����ˡ��������ĸ�С����ר����Ǯ���˺͹��ﵥ����
LONG );
	set("no_clean_up", 0);
	set("exits", ([
  		"east" : __DIR__"chenyu",
  		"down" : __DIR__"jiyuan",
  		"south" : __DIR__"xiuhua",
  		"west" : __DIR__"luoyan",
  		"north" : __DIR__"biyue",
	]));
        set("objects", ([
                "/d/beijing/npc/piaoke" : 1,
                "/d/beijing/npc/jinv" : 1,
        ]));
	set("coor/x", -160);
	set("coor/y", -20);
	set("coor/z", 20);
	setup();
	replace_program(ROOM);
}