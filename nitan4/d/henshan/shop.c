inherit ROOM;

void create()
{
	set("short", "С��");
        set("long", @LONG
�����Ǻ����سǵ�һ��С�꣬��Щ�򵥵���ʳ��ר��׬��Щ�ο�
��Ǯ��
LONG );
	set("exits", ([
		"north" : __DIR__"hengyang1",
		"up"    : __DIR__"huiyan",
	]));

	set("objects", ([
	        __DIR__"npc/xiaoer" : 1,
	]));

	set("coor/x", -10);
	set("coor/y", -120);
	set("coor/z", 0);
	setup();
	replace_program(ROOM);
}
