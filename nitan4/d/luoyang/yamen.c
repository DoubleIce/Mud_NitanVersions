// Room: /u/a/agah/yamen.c

inherit ROOM;

void create()
{
	set("short", "��������");
        set("long", @LONG
���϶����������ס������һ������������������ϸ������ǽ��
����һ�����ң����顺����������ĸ���������Ĵ��֡�֪��������
�İ����������飬ʦү�����ں�һ���������������ԣ��ڴ���ʲô
ԩ�������ֱ����֪��������˵��
LONG );
	set("no_clean_up", 0);
	set("exits", ([ /* sizeof() == 4 */
  "east" : __DIR__"neizhai",
  "south" : __DIR__"sting",
  "west" : __DIR__"yamendoor",
  "north" : __DIR__"bting",
]));

	set("coor/x", -150);
	set("coor/y", 20);
	set("coor/z", 10);
	setup();
	replace_program(ROOM);
}
