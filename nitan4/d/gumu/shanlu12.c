inherit ROOM;

void create()
{
        set("short", "ɽ·");
        set("long", @LONG
����һ���ǳ�������е�ɽ·��һ·��������ɽ���ϣ���;����
�����ĹŰ�ɽ�֣�εȻɭ�㡣�ڴ˴�����������ɽ�ľ�ɫ��ֻ��ɽ��
�����ɽ��ع�㣬��������һ����·������������һ�����ѵ�ɽ·��
LONG );
        set("outdoors", "quanzhen");
        set("exits", ([
                "northup"   : __DIR__"shanlu11",
                "southdown" : __DIR__"shanlu13",
        ]));

        setup();
        replace_program(ROOM);
}