inherit ROOM;

void create()
{
	set("short", "���ϴ�ϷԺ");
        set("long", @LONG
ϷԺ����һ���߸ߵ�Ϸ̨��̨��һЩ�����Ϲ�ױ���ˣ�����Ϸ����
���ŵ��ߣ��������㵸������ѽѽ�ĳ����й��Ĺ��⾩�磬̨���к�
�������ӣ�������Ϸ�ԣ�Ʊ�ѣ������²����Ŀ���̨�ϵı��ݣ�����
������̲�סվ���������һ�����á���
LONG );
	set("no_clean_up", 0);
	set("exits", ([
  		"east" : __DIR__"houtai",
  		"west" : __DIR__"sroad4",
	]));
        set("objects", ([
                "/d/beijing/npc/guanzhong" : 4,
                "/d/beijing/npc/xizi2" : 1,
                "/d/beijing/npc/xizi3" : 1,
        ]));
	set("coor/x", -160);
	set("coor/y", -10);
	set("coor/z", 10);
	setup();
	replace_program(ROOM);
}