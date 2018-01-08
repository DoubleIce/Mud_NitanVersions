#include <room.h>
inherit ROOM;

void create()
{
        set("short", "学堂");
        set("long", @LONG
这里是武馆内的一个小学堂，堂内阵阵朗朗读书声，一个先生在
这里认真的教着，这里放满了桌子和椅子，靠先生那边墙上写了几个
大字少壮不努力，老大徒伤悲。
LONG );
        set("no_fight", 1);
        set("exits", ([
                "south" : __DIR__"guofu_shilu-1",
        ]));
        set("objects", ([
                __DIR__"npc/zhuziliu" : 1,
        ]) );
        setup();
        replace_program(ROOM);
}
