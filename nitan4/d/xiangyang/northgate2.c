// Room: /d/xiangyang/northgate2.c
// Date: Jan. 8 1999 by Winder

inherit ROOM;
#include <ansi.h>;

void create()
{
	set("short", "玄武外门");
        set("long", @LONG
这里是襄阳城的北城门，只见城门上方刻着『玄武门』三个大字。
城门高三丈，宽约二丈有余，尺许厚的城门上镶满了拳头般大小的柳
钉。门洞长约四丈，大约每隔两个时辰就换官兵把守。近年来蒙古屡
次侵犯襄阳城，故这儿把守相当严密，城内一些官兵们正在盘查要离
襄阳城的人。
LONG );
        set("outdoors", "xiangyang");

	set("exits", ([
		"south"  : "/d/xiangyang/northgate1",
		"north"  : "/d/xiangyang/caodi3",
		"east"   : "/d/xiangyang/caodi1",
		"west"   : "/d/xiangyang/caodi2",
	]));
	set("objects", ([
		"/d/xiangyang/npc/pi"   : 1,
		"/d/xiangyang/npc/bing" : 2,
	]));
	set("coor/x", -300);
	set("coor/y", -20);
	set("coor/z", 0);
	setup();
	replace_program(ROOM);
}

