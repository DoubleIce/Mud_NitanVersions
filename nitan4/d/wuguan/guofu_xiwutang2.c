#include <room.h>

inherit ROOM;

void create()
{
        set("short", "习武堂");
        set("long", @LONG
这里是郭府的习武堂，堂内一个教头在教着武功，几个新手正在
向教头学习功夫，堂子正上方挂着个匾，上面写着吃得苦中苦，放为
人上人。
LONG );
        set("no_fight", 1);
        set("exits", ([
                "north" : __DIR__"guofu_shilu-2",
        ]));
        setup();
        replace_program(ROOM);
}
