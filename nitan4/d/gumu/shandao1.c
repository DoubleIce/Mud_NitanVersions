inherit ROOM;

void create()
{
        set("short", "ɽ��");
        set("long", @LONG
�˶�ɽ·�������ͱڿ�������ģ��ر�������С���ʱ�ͱڱ߱�
������ɽ赣���������������ǵ�ɽ�ﴵ��ʱ�������ر�С�ģ���Ȼ
һʧ�㣬��Ҫ����������Ԩ�ˡ���������һ����Ŀյء�������ͨ
����ɽ�ţ�ԶԶ��������һ���ϴ�ĺ���
LONG );
        set("outdoors", "quanzhen");
        set("exits", ([
                "southeast"   : __DIR__"shanlu7",
                "northdown"   : __DIR__"shandao2",
        ]));

        setup();
        replace_program(ROOM);
}
