inherit ROOM;

void create()
{
        set("short", "ͷ����");
        set("long", @LONG
ֻ����ʯ������ͨ��ɽ�ۣ�һ��ʯ����д��ͷ�����������֣���
���ʵ��䵱�������������㡣
LONG );
        set("exits", ([
                "north" : __DIR__"huixianqiao",
                "southup" : __DIR__"ertiangate",
        ]));
        set("outdoors", "wudang");
        set("no_clean_up", 0);
	set("coor/x", -350);
	set("coor/y", -390);
	set("coor/z", 150);
	setup();
        replace_program(ROOM);
}