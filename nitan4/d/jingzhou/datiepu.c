inherit ROOM;

void create()
{
	set("short", "������");
        set("long", @LONG
����һ�Ҽ�ª�Ĵ����̣����İ���һ����¯��¯��������յ�һ
Ƭͨ�죬��һ�߽�ȥ�͸е�������ȡ�ǽ�Ƕ��������깤��δ�깤��
�˵���������������ذ�ס����׵��һλ������ͷ�󺹻�����������
ר����־���ڴ�����
LONG );
	set("exits", ([
		"west" : __DIR__"nandajie1",
	]));
        set("objects", ([
                 __DIR__"npc/smith": 1,
	]));
	set("coor/x", -440);
	set("coor/y", -220);
	set("coor/z", 20);
	setup();
	replace_program(ROOM);
}

