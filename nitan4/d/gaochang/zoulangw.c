#include <ansi.h>
inherit ROOM;

string look_wall();

void create()
{
        set("short", "走廊");
        set("long", @LONG
这里是殿堂走廊。房顶一侧支在南面的高墙上，另一侧则与北边
殿堂的屋顶相连。彩梁画栋，连顶棚也用彩漆绘满了各种飞天的图形，
每幅画似乎都在诉说着一个娓娓动人的佛经故事。南边的墙壁(wall)
上题着一个字。
LONG );
        set("exits", ([
                "southeast" : __DIR__"wroom3",
                "northeast" : __DIR__"zoulang2",
        ]));

        set("item_desc",([
                "wall" : (: look_wall :),
        ]));
        setup();
        replace_program(ROOM);
}

string look_wall()
{
        return WHT "\n"
"       文文文文文文文文文文文文文文文文文文文\n"
"       文文文文文文文文    文文文文文文文文文\n"
"       文文文文文文文文文    文文文文文文文文\n"
"       文文文                          文文文\n"
"       文文文文文文  文文文文文  文文文文文文\n"
"       文文文文文文文  文文文  文文文文文文文\n"
"       文文文文文文文文  文  文文文文文文文文\n"
"       文文文文文文文文    文文文文文文文文文\n"
"       文文文文文文文  文文  文文文文文文文文\n"
"       文文文文文文  文文文文  文文文文文文文\n"
"       文文文文    文文文文文文    文文文文文\n"
"       文文    文文文文文文文文文    文文文文\n"
"       文文文文文文文文文文文文文文文文文文文\n"
"       文文文文文文文文文文文文文文文文文文文\n\n\n" NOR;
}
