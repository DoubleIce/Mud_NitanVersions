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
                "south" : __DIR__"eroom2",
                "northeast" : __DIR__"zoulange",
        ]));

        setup();
        replace_program(ROOM);
}
