inherit ROOM;

void create()
{
        set("short", "ɽ��");
        set("long", @LONG
�˶�ɽ·�������ͱڿ�������ģ��ر�������С���ʱ�ͱڱ߱�
������ɽ赣�������������䵱ɽ�ﴵ��ʱ�������ر�С�ģ���Ȼһ
ʧ�㣬��Ҫ����������Ԩ�ˡ�����������һ����Ŀյء�������ͨ
����ɽ�ţ�ԶԶ��������һ���ϴ�ĺ���
LONG );
        set("outdoors", "quanzhen");
        set("exits", ([
                "southup"   : __DIR__"shandao1",
                "northdown" : __DIR__"shulin10",
        ]));

        setup();
        replace_program(ROOM);
}
