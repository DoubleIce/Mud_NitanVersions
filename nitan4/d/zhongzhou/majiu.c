#include <room.h>
inherit TRANS_ROOM;

void create()
{
      set("short", "马厩");
        set("long", @LONG
这里是中州城英豪酒楼后的马厩，常年供应新鲜草料。中州城自
古乃军事要地，民风淳朴，马夫们会把马牵到马厩好生照看，将它们
喂饱饮足，再洗刷得干乾净净，一直伺候到客人上路。马厩雨檐下的
烂木柱上钉着一块破木牌 (paizi)。马厩中堆放著几堆草料，正中有
一口泔槽。
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
