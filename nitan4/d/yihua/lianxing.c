// ROOM : lianxin.c
inherit ROOM;
void create()
{
  set("short","���ǹ�");
        set("long", @LONG
�������¹�����Ϣ�ĵط���ֻ��һ�������ã�ò���绨��Ů��
վ���ڻ����У��������书��ߣ�������ص��ƻ�����������ǰ��
Ϊ���Ľ�����¹����������������������ǳ������ˣ������������
��ò�Ҫ�ӽ�����
LONG );
  set("exits",([
      "east" : __DIR__"changlang1",
      "southeast" : __DIR__"woshi",
     ]));
  set("objects",([
        //__DIR__"npc/lianxing" : 1,
     ]));
 setup();
 replace_program(ROOM);
}
