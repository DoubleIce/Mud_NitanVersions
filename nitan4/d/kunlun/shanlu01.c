inherit ROOM;

void create()
{
	set("short", "ɽ·");
        set("long", @LONG
�����Ѿ��������ɵĵط��ˣ�·�߻������أ������Ǻ������ڣ�
����ȴ��Ȼ���������������������޵Ľ�����ǰ��ɽ�Ͼ��������ɵ�
�����ˣ�����������ʱ���ɽ�š�
LONG );
	set("exits",([
		"westdown" : __DIR__"shanmen",
		"southup" : __DIR__"shanlu02",
	]));

	set("outdoors", "����");
	setup();
	replace_program(ROOM);
}
