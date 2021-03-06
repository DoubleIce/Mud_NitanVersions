// Room: /d/xiangyang/westgate2.c
// Date: Jan. 8 1999 by Winder

inherit ROOM;
#include <ansi.h>;

void create()
{
	set("short", "白虎外门");
        set("long", @LONG
这里是襄阳城的西城门，只见城门上方刻着『白虎门』三个大字。
城门高三丈，宽约二丈有余，尺许厚的城门上镶满了拳头般大小的柳
钉。门洞长约四丈，大约每隔两个时辰就换官兵把守。近年来蒙古屡
次侵犯襄阳城，故这儿把守相当严密，城内一些官兵们正在盘查要离
襄阳城的人。
LONG );
        set("outdoors", "xiangyang");

	set("exits", ([
		"east"  : "/d/xiangyang/westgate1",
                "west"  : "/d/city2/yidao1",
	]));
	set("objects", ([
		"/d/xiangyang/npc/pi"   : 1,
		"/d/xiangyang/npc/bing" : 2,
	]));
	set("coor/x", -350);
	set("coor/y", -80);
	set("coor/z", 0);
	setup();
	replace_program(ROOM);
}

