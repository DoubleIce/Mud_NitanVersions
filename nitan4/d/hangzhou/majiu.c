#include <room.h>
inherit TRANS_ROOM;

void create()
{
      set("short", "马厩");
        set("long", @LONG
这是天外天客店后的马厩，常年供应新鲜草料。杭州自古号称天
堂，杭州的客店汇集四海宾客。马夫们会把马牵到马厩好生照看，将
它们喂饱饮足，再洗刷得干乾净净，伺候到客人上路。马厩雨檐下的
烂木柱上钉着块破木牌 (paizi)。马厩中堆放著几堆草料，正中有一
口泔槽。
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
