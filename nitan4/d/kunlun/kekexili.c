inherit ROOM;

void create()
{
          set("short", "可可西里山");
        set("long", @LONG
可可西里山又称可可稀立山，蒙古语意为「青山」的意思。西起
木孜塔格峰，东接巴颜喀拉山，山势平缓，冻土广布，高处少永久性
积雪与冰川。除北侧有淡水湖钦马湖外，其余南北星罗棋布的湖泊均
为咸水湖。草木稀疏，人烟极少。
LONG );
         set("exits",([
                "northwest" : __DIR__"shankou",
                "east" : __DIR__"bayankala",
         ]));
         set("outdoors", "kunlun");
         setup();
         replace_program(ROOM);    
}
