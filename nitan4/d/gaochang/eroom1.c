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
                "north" : __DIR__"eroom2",
                "west"  : __DIR__"dadian",
        ]));
        setup();
        replace_program(ROOM);
}
