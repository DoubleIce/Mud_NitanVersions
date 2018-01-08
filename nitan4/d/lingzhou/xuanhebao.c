#include <ansi.h>
#include <room.h>
inherit RIVER;

void create()
{
	set("short", "宣和堡");
        set("long", @LONG
这里就是西北小镇宣和堡，南面是黄河，西面是沙漠，只有这里
有片不大的绿洲，住户们都是从关内迁移过来的，大多以经营手工艺
品为生，这里的手织羊毛挂毯颇有名气。每逢节日附近的百姓都来到
这摆渡过河 (river)到关内去赶集。河案边熙熙攘攘，人们都在挣着
叫船过河。
LONG );
        set("arrive_room", "/d/huanghe/guchangcheng");
	set("exits", ([
		"northeast" : __DIR__"mingshazhou",
	]));

        set("resource/fish", ({ "/clone/fish/liyu",
                                "/clone/fish/jiyu",
                                "/clone/fish/qingyu",
                                "/clone/fish/caoyu", }));

	set("outdoors", "lingzhou");
        setup();
        replace_program(RIVER);
}

