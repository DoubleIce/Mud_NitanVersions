inherit ROOM;

void create()
{
        set("short", "С�Ե�");
        set("long", @LONG
��һ�߽��������ŵ�һ��ŨŨ��С����ζ����վ���ſھ���һ��
��úó�һ�ٵĸо������Ű�����һ���ſ��������˿��ˣ������̸
Ц����ͷ�Ӷ����������������������ϵ��ƹʺ�ҥ�ԣ����ﵹ��
�������ڡ�С��������֮�䴩����ȥ��æ�ø����������к��㡣
LONG );
        set("resource/water", 1);
        set("exits", ([
                "east" : __DIR__"beidajie2",
        ]));
        set("objects", ([
                __DIR__"npc/xiaoer2" : 1,
        ]));

        set("coor/x", -520);
	set("coor/y", 130);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}
