//room: xianchou.c
inherit ROOM;

void create()
{
  set("short","С��");
        set("long", @LONG
�㻬��ȵأ�ͻȻһ���������ˣ�ʹ���������У��ƺ���������
ò�绨��Ů��վ��·�У��㲻����������ʹ������ǰ��ȥ֮�����ʻ�
�����ƺ������Ǳ���
LONG );
  set("outdoors", "yihua");
  set("exits",([
      "south" : __DIR__"yihua_in",
      "up" : __DIR__"juebi",
     ]));

 setup();
 replace_program(ROOM);
}
