inherit ROOM;

void create()
{
	set("short", "С��ͬ");
        set("long", @LONG
���������������ϰ��յľ�ס������ͬ�ںܰ�����û��ʲô������
һЩ������������������Խ����ͬ���ߣ�һЩȫ�����Ű�ɫ���µ�
�˾�Խ���ˣ�ֻ����Щ�˹�����������㱣����ٿ��ɣ����˲²�
͸�Ǹ�ʲô�ġ�
LONG );
        set("outdoors", "luoyang");
        set("no_clean_up", 0);
        set("exits", ([
  		"north" : __DIR__"suanming",
  		"south" : __DIR__"hutong2",
  		"west" : __DIR__"roudian",
	]));
        set("objects", ([
                "/d/kaifeng/npc/qigai" : 1,
        ]));
	set("coor/x", -120);
	set("coor/y", 30);
	set("coor/z", 10);
	setup();
	replace_program(ROOM);
}