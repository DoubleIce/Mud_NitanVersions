#include <ansi.h>
#include <room.h>
inherit RIVER;

void create()
{
	set("short", "古长城");
        set("long", @LONG
这里是一段古长城。相传是当年秦始皇派他的心腹爱将蒙恬率三
十万大军所修。世事变迁、沧海桑田，如今这里已是片废墟，唯一依
稀可见的是夯土制成的烽火台象个小土包一样矗立在那里。黄河从西
向东流去，河上(river)有一叶小舟。
LONG );
        set("arrive_room", "/d/lingzhou/xuanhebao");
	set("exits", ([
		"southwest" : __DIR__"yinpanshui",
		"southeast" : __DIR__"shimen",
	]));
	set("objects", ([
		__DIR__"npc/menmian" :1,
	]));

        set("resource/fish", ({ "/clone/fish/liyu",
                                "/clone/fish/jiyu",
                                "/clone/fish/qingyu",
                                "/clone/fish/caoyu", }));

	set("outdoors", "huanghe");
	set("coor/x", -20);
	set("coor/y", 170);
	set("coor/z", 0);
	setup();
        replace_program(RIVER);
}
