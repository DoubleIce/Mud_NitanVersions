inherit ROOM;

void create()
{
        set("short", "�����");
        set("long", @LONG
ÿһ�䷿�д󶼹��з���żȻ�ڱ��ϼ����������ģ�д���Ǹ�
������������̩���������ʮ����ȵ���������һ�������й��Ķ���
������������д�Ŵ����ʥ��ʦ����λ�����Ҹ�����ʮ�ˣ�д����
�ء���·���ӹ������ġ����ŵ����֡�
LONG );
        set("exits", ([
                "east" : __DIR__"dadian",
                "north" : __DIR__"wroom2",
        ]));

        setup();
        replace_program(ROOM);
}
