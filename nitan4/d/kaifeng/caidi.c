inherit ROOM;

void create()
{
        set("short", "�˵�");
        set("long", @LONG
��Ƭ��԰�Ӽ����������һЩʱ���߲ˡ������м���ľ׮�����
�˼��ӣ���һЩ���ٵ��߲��������������Ŀ��ȥ���ϴ��һƬ��԰
�ӣ���Ȼ���������û�м��òˡ�
LONG );
        set("no_clean_up", 0);
        set("exits", ([
		"south" : __DIR__"caidi4",
		"west" : __DIR__"zoulang2",
  		"north" : __DIR__"caidi3",
  		"east" : __DIR__"caidi5",
	]));
        set("outdoors", "kaifeng");

        setup();
        replace_program(ROOM);
}