// Code of ShenZhou
// wsky, 5/7/00
inherit ROOM;

#include <ansi.h>
#include "xx_job.h"

void setup_npc(object me, object ob);

void create()
{
        set("short", "星宿密林");
        set("long", @LONG
这里是星宿海旁边的森林，高大的松树几乎把所有的光线都遮掩
住了。地上到处都是残枝败叶，每踏出一步都会发出吱吱的声响，远
处不时传来一阵阵枭鸣，使人毛骨悚然。
LONG );

        set("exits", ([ 	
	     "south" : "/d/xingxiu/forest1",
	     "west" : "/d/xingxiu/saimachang",
        ]));
/*
        set("objects", ([
                "/d/xingxiu/npc/sangtu"  : 1,
        ]) );
*/
        set("no_clean_up", 0);

        set("outdoors", "xingxiuhai");

        set("cost", 2);
        setup();
        

}
