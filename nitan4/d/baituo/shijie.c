inherit ROOM;

void create()
{
	set("short", "ʯ��");
        set("long", @LONG
��������ʯ���̳ɵ�ʯ���ϡ�������Ǵ�˵�����صİ���ɽ��Զ
Զ��ȥ��������ɳ�ѻ��γɵ�ɽ�����һֻ���յļ�����һ��ɽ����
�������ǰ��
LONG );
	set("exits", ([
		"east"      : __DIR__"caoping",
		"northup"   : __DIR__"damen",
		"southdown" : __DIR__"guangchang" ,
	]));
	set("outdoors", "baituo");
	setup();
	replace_program(ROOM);
}
