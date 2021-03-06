// Room: /city/market.c
// YZC 1995/12/04
#include <ansi.h> 
#include <room.h>
inherit ROOM;

int is_chat_room() { return 1;}

void create(){
	set("short", "集市");
        set("long", @LONG
这里是扬州集市，人来人往熙熙攘攘。很多小贩子喜欢在这里经
商，虽然大部分东西都是任务日常用品，但是其中也不乏一些珍稀之
物。如果玩家眼光好，可以从这里付出少量金钱得到自己想要的东东。
LONG );

        set("outdoors", "city");
	set("no_fight", "1");
	set("no_steal", "1");
	set("no_sleep_room","1");
        set("valid_startroom","1");

        set("objects", ([ 
                "/d/city/npc/qi"     : 1, 
                "/adm/npc/beastseller" : 1,
        ])); 

	set("exits", ([
                "north" : "/d/city/dongdajie3",
	]));
	set("coor/x", 30);
	set("coor/y", -10);
	set("coor/z", 0);
	setup();
}
