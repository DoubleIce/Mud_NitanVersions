inherit ROOM;

void create()
{
	set("short", "��ٵ�");
        set("long", @LONG
����һ��������ֱ����������Ĵ�ٵ�������ݵ���ʮ�����ۡ�
����ͨ�򺯹ȹؿ��Դ����ݳǣ���������Ե��ﶫ�������ųǡ�
LONG );
        set("outdoors", "luoyang");
        set("no_clean_up", 0);
        set("exits", ([
  		"west" : __DIR__"guandaoe1",
  		"east" : __DIR__"guandaoe3",
	]));

	set("coor/x", -80);
	set("coor/y", 0);
	set("coor/z", 0);
	setup();
	replace_program(ROOM);
}