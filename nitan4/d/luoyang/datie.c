inherit ROOM;

void create()
{
	set("short", "������");
        set("long", @LONG
����һ��������¡�Ĵ����̣����İ���һ����¯��¯���������
��һƬͨ�죬��һ�߽�ȥ�͸е�������ȡ�ǽ�Ƕ��������깤��δ��
���Ĳ˵���������������ذ�ס����׵��һλ������ͷ�󺹻�����
������ר����־���ڴ��������������ϰ��֮�˶�ϲ������������
�ֵ�������ǽ���п�����(paizi)��
LONG );
	set("no_clean_up", 0);
	set("exits", ([
  		"east" : __DIR__"sroad5",
	]));
        set("item_desc",([
                "paizi" : "�޲���������(repair xxx)��\n",
        ]));
        set("objects", ([
                __DIR__"npc/smith" : 1,
        ]));
	set("coor/x", -180);
	set("coor/y", -20);
	set("coor/z", 10);
	setup();
	replace_program(ROOM);
}
