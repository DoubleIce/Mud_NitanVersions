inherit ROOM;

void create()
{
        set("short", "���");
        set("long", @LONG
������һ����ʯ����ϣ���������������ͨ�������������ݡ�
������һ����ǳأ�����ǽ������Ʈ�������ǳ����ˡ�������ȥ
һƬ�����ͻ�Ұ��
LONG );
        set("exits", ([
            "east"  : "/d/changan/xi-chengmen",
            "west"  : __DIR__"xxroad2",
        ]));
        set("outdoors", "changan");
        set("coor/x", -460);
	set("coor/y", 0);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}
