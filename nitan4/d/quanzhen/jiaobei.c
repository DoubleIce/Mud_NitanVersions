// jiaobei.c 教碑
// By Lgg,1998.10

#include <ansi.h>
inherit ROOM;

void create()
{
        set("short", "教碑");
        set("long", @LONG
这里是全真教的教碑所在地，路旁立着一块大碑(bei)。再往东走
就是天下闻名的道家玄门正宗--全真教的大门了。北面有一条石阶，
不知道通向哪里，往西是下山的路。
LONG );
        set("outdoors", "quanzhen");
        set("exits", ([
                "south"   : "/d/quanzhen/dajiaochang",
                "northup" : "/d/quanzhen/shijie6",
                "eastup" : "/d/quanzhen/damen",
                "west" : "/d/quanzhen/shijianyan",
        ]));
        set("item_desc", ([
        "bei": CYN"
        ＊＊＊＊＊
　　　　＊　　　＊
　　　　＊　全　＊
　　　　＊　　　＊
　　　　＊　真　＊
　　　　＊　　　＊
　　　　＊　古　＊
　　　　＊　　　＊
　　　　＊　教　＊
　　　　＊　　　＊
　　　　＊＊＊＊＊
\n"NOR
        ]) );
        set("objects",([
                CLASS_D("quanzhen") + "/zhou" : 1,
        ]));

        setup();
        replace_program(ROOM);
}


