inherit ROOM;

#include "langqun.h"

void create()
{
        set("short", "高昌废墟");
        set("long", @LONG
站在这里一眼望去，高高矮矮的房子栉比鳞次，可是声息全无，
甚至雀鸟啾鸣之声亦丝毫不闻。如此可怖的景象，寂静的气势使人连
大气也不敢喘上一口。一片寂静之中，远处忽然传来隐隐的狼嗥。
LONG );
        set("outdoors", "gaochang");
        set("exits", ([ 
                "east" : __DIR__"feixu1",
                "west" : __DIR__"pendi",
		"north" : __DIR__"xiaowu",
	]));

        setup();
}
