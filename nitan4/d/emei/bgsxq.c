inherit ROOM;

void create()
{
      set("short", "��ǽ");
        set("long", @LONG
�����Ƕ�üɽ�����µ���ǽ����Ժ���������ǽ�Ǳ�Ʈ�����ڿ�
���л��졣һ��ɽϪ������ɽ�ϵĽ����������������ɽ����ȥ��
LONG );
      set("outdoors", "emei");
      set("exits", ([
          "east"      : __DIR__"bgs",
      ]));
      set("no_clean_up", 0);
	set("coor/x", -380);
	set("coor/y", -220);
	set("coor/z", 10);
	setup();
      replace_program(ROOM);
}