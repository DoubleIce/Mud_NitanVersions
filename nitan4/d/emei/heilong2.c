inherit ROOM;

void create()
{
      set("short","������ջ��");
        set("long", @LONG
������ջ���غ���������������һɽ�п������²������γ�һ��
�������ߣ����Ｘ���׵���Ͽ��������Ͽ��������ջ���ʹ���խ�İ�
��Ͽ��ת�۴����������ھ����ϡ�����ջ����ֻ����խ��Σ��������
��������������ɽ��������������ͷ�������϶���¿������ϡ����
���쿪��ͼ�ġ�һ���졹��ջ����ͨǧ���֣�����������
LONG );
      set("outdoors", "emei");
      set("exits", ([
          "west"  : __DIR__"qianfoan",
          "north" : __DIR__"heilong1",
      ]));
      set("no_clean_up", 0);
      set("coor/x", -460);
	set("coor/y", -240);
	set("coor/z", 100);
	set("coor/x", -460);
	set("coor/y", -240);
	set("coor/z", 100);
	setup();
      replace_program(ROOM);
}