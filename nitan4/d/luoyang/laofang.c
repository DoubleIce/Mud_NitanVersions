inherit ROOM;

void create()
{
	set("short", "�η�");
        set("long", @LONG
�������η������涼��������Χס��������һ��С�������ţ���
��ߴ���һ�ȴ�������͸����΢���Ĺ��ߴӴ������˽����������η�
����һ����������������һЩ���񼫵ķ��ˡ�
LONG );
	set("no_clean_up", 0);
	set("exits", ([
  		"south" : __DIR__"xunbu",
	]));
        set("objects", ([
                "/clone/npc/walker" : 1,
        ]));
	set("coor/x", -200);
	set("coor/y", 20);
	set("coor/z", 10);
	setup();
	replace_program(ROOM);
}