inherit ROOM;

void create()
{
	set("short", "�洢��");
        set("long", @LONG
�����ǵ��̵Ĵ洢�ң����ڴ洢һЩ�ѱ��䵱���������ܱ�����
��صĶ�������Ȼ��ֻ����ʱ�ģ�ֻҪһ���˿���ص����ޣ�������
��������ԥ�Ľ���߼۳��ۣ�Ҫ֪�����˳���Ǯ��ʲôҲ�����ϵġ�
������ɭ�ڰ���ʪ�����ҿ����л������һ��ùζ��
LONG );
	set("no_clean_up", 0);
	set("exits", ([
  		"up" : __DIR__"dangpu",
	]));

	set("coor/x", -180);
	set("coor/y", 20);
	set("coor/z", 0);
	setup();
	replace_program(ROOM);
}
