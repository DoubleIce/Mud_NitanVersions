inherit ROOM;

void create()
{
        set("short", "��ɼ��");
        set("long", @LONG
������һƬ�����޾��Ĵ��̵����֣����ܵ���ɼ�����ľ�ɡ��
���ص�����֦Ѿ��ֻ©�°߰ߵ��ϸ�����Ӱ��������ʮ���ľ�����
��ȸҲ�ٷ�����ֻż��������Զ���ļ���������
LONG );
	set("exits",([
		"west"  : __DIR__"shanlin" + (random(5) + 1),
		"south" : __DIR__"shanlin5",
		"north" : __DIR__"shanlin" + (random(5) + 1),
		"east"  : __DIR__"shanlin" + (random(5) + 1),
	]));

	set("outdoors", "kunlun");
	setup();
	replace_program(ROOM);
}