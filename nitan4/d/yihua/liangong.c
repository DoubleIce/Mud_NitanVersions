//room: liangong.c

inherit ROOM;

void create()
{
  set("short","������");
        set("long", @LONG
�������ƻ������������ĵط����м�������Ů������ר�����µ�
���䣬��������Ϊ�ƻ������书�ر�������������Ϊ���ƻ��������
�����������ú�Ͷ�롣
LONG );

  set("exits",([
      "east" : __DIR__"yihua_ge",
          ]));

  set("objects",([
      "/clone/npc/mu-ren" : 4 ]));
  setup();
 replace_program(ROOM);
}