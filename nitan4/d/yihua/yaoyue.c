// ROOM : yaoyue.c
inherit ROOM;
void create()
{
  set("short","���¹�");
        set("long", @LONG
�������¹�����Ϣ�ĵط���ֻ��һ��������ã� ò���绨��Ů��
վ���ڻ����У��������书��ߣ��������ص��ƻ�����������ǰ��
Ϊ�������������������ǳ������ˣ��������������ò�Ҫ�ӽ�����
LONG );
  set("exits",([
      "west" : __DIR__"changlang1",
      "southwest" : __DIR__"woshi",
     ]));
  set("objects",([
        //__DIR__"npc/yaoyue" : 1,
     ]));
 setup();
 replace_program(ROOM);
}