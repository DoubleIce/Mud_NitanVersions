inherit ROOM;

void create()
{
        set("short", "����");
        set("long", @LONG
���ȵĵذ�������ߣ�����ԭ�����ǲ�԰�ӣ��ԴӶ�������ס��
����Ƥ֮���⼸�������û�����ˡ����滹�����������и�С��ͨ
����ի������������ζ�ʹ�����Ʈ�˳�����
LONG );
        set("no_clean_up", 0);
        set("exits", ([
  		"west" : __DIR__"chufang2",
  		"east" : __DIR__"zoulang2",
	]));
        set("outdoors", "kaifeng");

        setup();
        replace_program(ROOM);
}