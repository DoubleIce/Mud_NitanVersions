inherit ROOM;

void create()
{
	set("short", "����");
        set("long", @LONG
���������Ŷ�������֪���д����˵����ڡ����а���һ��ɼľԲ
���ͼ������ӣ�������һ�׾��µ����˴�����ǽ�Ϲ���һ�����ã���
�����ͻ���ɽ������֪�����ֱʡ�
LONG );
	set("no_clean_up", 0);
	set("exits", ([
  		"north" : __DIR__"yamen",
	]));

	set("coor/x", -150);
	set("coor/y", 10);
	set("coor/z", 10);
	setup();
	replace_program(ROOM);
}