inherit ROOM;

void create()
{
        set("short", "�ڳ�����");
        set("long", @LONG
�����ڳ����Ÿ����ɣ���Լ�������࣬������ĳ�����������ȭ
ͷ���С���������Ŷ���Լ���ɣ���Լÿ������ʱ���ͻ��ٱ����ء�
��������������׽��֮��Ĺٸ�ͨ����һ����ֱ����ʯ��������
�������죬��ȥ���������ڳ��ˣ�����һ�Ÿ߸߿�������ǻ��Ǻӡ�
LONG );
        set("outdoors", "luoyang");
        set("no_clean_up", 0);
        set("exits", ([
                "east" : __DIR__"wroad7",
                "west" : __DIR__"wbridge",
        ]));
        set("objects", ([
                "/d/kaifeng/npc/guanbing" : 4,
                "/d/beijing/npc/ducha" : 1,
                "/clone/npc/walker" : 1,
        ]));
        set("coor/x", -230);
	set("coor/y", 0);
	set("coor/z", 10);
	setup();
        replace_program(ROOM);
}
