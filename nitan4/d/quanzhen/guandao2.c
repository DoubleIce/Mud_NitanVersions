inherit ROOM;

void create()
{
        set("short", "�ٵ�");
        set("long", @LONG
����һ���ٸ��޽��Ĵ����������Լ���Կ����书��Ķ��š�Զ
��������Կ���Ρ��ĳ�ǽ��������ͨ����ԭ��·�������������
�����֡�Ȱ������һ���ƣ����������޹��ˡ��ĸо���
LONG );
        set("outdoors", "wugong");
        set("exits", ([
                "east" : __DIR__"guandao1",
                "west" : __DIR__"dongmen",
        ]));
        set("no_clean_up", 0);
        setup();
        replace_program(ROOM);
}
