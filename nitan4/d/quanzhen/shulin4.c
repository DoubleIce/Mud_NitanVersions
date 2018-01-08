// Code of ShenZhou
// road: /zhongnan/shulin4.c

inherit ROOM;

void create()
{
        set("short","树林");

        set("long", @LONG
这位於终南山间的一大片树林，生的颇为茂密。走在其间，只听
得脚下沙沙的落叶声，四周昏昏暗暗的，不时几道日光穿过浓密的枝
头，投射而下。偶而远处几声兽吼声，更添了一份神密感。往北、南
各有一条小径。
LONG );

        set("exits",([ 
                "north" : __DIR__"shulin3",
                "south" : __DIR__"shulin5",
        ]));
        set("outdoors", "quanzhen");

        setup();

}

#include "caiyao.h"

