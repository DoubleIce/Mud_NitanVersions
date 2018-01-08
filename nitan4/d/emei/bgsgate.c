#include <ansi.h>
inherit ROOM;

string look_gate();

void create()
{
        set("short", "报国寺山门");
        set("long", @LONG
报国寺为峨嵋出入之门户。山门(gate)上有一块大匾。寺外苍楠
环卫，翠柏掩映。由此一路向西上开始登峨嵋山，北面下山是一条弯
弯的石阶路。
LONG );
        set("outdoors", "emei");
        set("item_desc", ([
                "gate" : (: look_gate :),
        ]));
        set("objects", ([
                __DIR__"npc/guest": 1,
        ]));
        set("exits", ([
                "northdown" : __DIR__"qsjie2",
                "south"     : __DIR__"bgs",
        ]));
	set("coor/x", -370);
	set("coor/y", -210);
	set("coor/z", 10);
	setup();
}

string look_gate()
{
      return
RED "\n\n　　　　≌≌≌≌≌≌≌≌≌≌≌≌≌≌≌≌≌\n"
"　　　　≌≌　　　　　　　　　　　　　≌≌\n"
"　　　　≌≌" WHT "　　　报　　国　　寺" RED "　　　≌≌\n"
"　　　　≌≌　　　　　　　　　　　　　≌≌\n"
"　　　　≌≌≌≌≌≌≌≌≌≌≌≌≌≌≌≌≌\n\n\n";
}
