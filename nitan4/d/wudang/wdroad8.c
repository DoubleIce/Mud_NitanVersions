inherit ROOM;

void create()
{
        set("short", "С·");
        set("long", @LONG
�������������ڡ�һ�������ĵĻ���·��������ЩС���ݣ�����
����ġ���·�����˺��٣�����ɫ�Ҵ���ǰ��·��
LONG );
        set("outdoors", "wudang");
        set("exits", ([
                "northeast" : __DIR__"wdroad7",
                "west"      : __DIR__"sanbuguan",
        ]));
        set("objects", ([
		__DIR__"obj/shitou":1,
        ]));
	set("coor/x", -320);
	set("coor/y", -160);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}