#include <room.h>
inherit ROOM;

void create()
{
	set("short", "韦府书房");
        set("long", @LONG
这里是韦公爷的书房，房间宽敞明亮，正对着门是一大红木书桌，
书桌旁一个六尺高的黄铜香炉，四周的书架上堆放满了各种书籍，不
过很容易看出已经很就没人动过了。
LONG );

	set("exits", ([
		"south" : "/d/beijing/weifu_dating",
	]));
	set("objects", ([
		"/d/beijing/npc/shizhe" : 1,
	]));
	set("coor/x", -30);
	set("coor/y", 310);
	set("coor/z", 0);
	setup();
}
