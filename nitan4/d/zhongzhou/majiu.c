#include <room.h>
inherit TRANS_ROOM;

void create()
{
      set("short", "����");
        set("long", @LONG
���������ݳ�Ӣ����¥������ǣ����깩Ӧ���ʲ��ϡ����ݳ���
���˾���Ҫ�أ���紾�ӣ������ǻ����ǣ�����Ǻ����տ���������
ι�����㣬��ϴˢ�ø�Ǭ������һֱ�ź򵽿�����·�����������µ�
��ľ���϶���һ����ľ�� (paizi)�������жѷ������Ѳ��ϣ�������
һ����ۡ�
LONG );
      set("outdoors", "zhongzhou");
      set("no_fight", 1);
      set("objects", ([
              "/clone/horse/zaohongma": 1,
              "/clone/horse/huangbiaoma": 1,
              "/clone/horse/ziliuma": 1,
              "/clone/npc/mafu": 1,
      ]));
      set("exits",([
              "west" : __DIR__"yinghao",
              "up"   : "/clone/shop/zhongzhou_shop",
      ]));
      set("coor/x", -210);
	set("coor/y", 0);
	set("coor/z", 0);
	setup();
      replace_program(TRANS_ROOM);
}