// Room: /u/a/agah/kefang2.c

inherit ROOM;

void create()
{
	set("short", "�Ͽͷ�");
        set("long", @LONG
����һ��ܴ�Ŀͷ���������Ȼ�򵥣���ʮ�ָɾ����ࡣ��ǽ��
��ʮ����Сľ�������ٿ��������¶��ԣ������Ӷ��Ǻ����Ĵ�����
��ʱ�Ļ��п��˽���˯������˯�õ��˺��Ծ������������߳��ͷ���
LONG );
	set("no_clean_up", 0);
	set("exits", ([ /* sizeof() == 1 */
  "north" : __DIR__"kezhan2",
]));

	set("coor/x", -160);
	set("coor/y", 10);
	set("coor/z", 20);
	setup();
	replace_program(ROOM);
}