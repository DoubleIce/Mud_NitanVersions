#include <room.h>
inherit TRANS_ROOM;

void create()
{
      set("short", "����");
        set("long", @LONG
����������͵������ǣ����깩Ӧ���ʲ��ϡ������Թźų���
�ã����ݵĿ͵�㼯�ĺ����͡������ǻ����ǣ�����Ǻ����տ�����
����ι�����㣬��ϴˢ�ø�Ǭ�������ź򵽿�����·�����������µ�
��ľ���϶��ſ���ľ�� (paizi)�������жѷ������Ѳ��ϣ�������һ
����ۡ�
LONG );
      set("exits",([
                "west" : __DIR__"kedian",
                "up"   : "/clone/shop/hangzhou_shop",
                "north" : __DIR__"business",
      ]));
      set("outdoors", "hangzhou");
      set("no_fight", 1);
      set("objects", ([
                "/clone/horse/zaohongma": 1,
                "/clone/horse/huangbiaoma": 1,
                "/clone/horse/ziliuma": 1,
                "/clone/npc/mafu": 1,
      ]));
      setup();
      replace_program(TRANS_ROOM);
}