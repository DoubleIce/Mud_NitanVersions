// Room: /d/xiangyang/duchang.c
// Date: Jan. 8 1999 by Winder

inherit ROOM;

void create()
{
	set("short", "�ĳ�");
        set("long", @LONG
���ﱾ���������Ķĳ������Ǵ�ս��ǰ��Ϊ���ؾ����Ķ�ҡ��
���Ͱܻ�����������������ر��˶ĳ����ſ���ȸ�Ĵ�Ժ����������
��ʱ�Ĺ�ģ�������ưܵĶľߣ�Ҳ��֪������������˵ʲô��
LONG );
	set("no_clean_up", 0);

	set("exits", ([
		"east" : "/d/xiangyang/southjie2",
	]));
	set("coor/x", -300);
	set("coor/y", -110);
	set("coor/z", 0);
	setup();
	replace_program(ROOM);
}