// ROOM : linjxd6.c
inherit ROOM;
void create()
{
  set("short","�ּ�С��");
        set("long", @LONG
������һ���������ּ�С���ϣ���������ɭɭ�����֡�һ�����
�������ң�����ɳɳ�����������㲻��������
LONG );
  set("exits",([
      "south" : "/d/heimuya/linjxd1",
      "north" : "/d/heimuya/linjxd4",     
      "east"  : "/d/heimuya/linjxd3",
      "west"  : "/d/heimuya/dating2",
  ]));
  set("no_clean_up", 0);
  setup();
  replace_program(ROOM);
}