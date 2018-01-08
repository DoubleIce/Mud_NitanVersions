#include <ansi.h>

inherit ROOM;

void create()
{
        set("short", "汇英酒楼二楼");
        set("long", @LONG
酒楼里桌椅洁净。座中客人衣饰豪奢，十九是富商大贾。这里可
以俯瞰整个紫禁城的全景。
LONG );
        set("exits", ([
                "down" : "/d/beijing/huiying",
        ]));
        set("objects", ([
                "/d/tulong/yitian/npc/zhaomin2" : 1,
                "/d/tulong/yitian/npc/zhao1" : 1,
                "/d/tulong/yitian/npc/qian2" : 1,
        ]));
        set("outdoors", "beijing");
        setup();
        replace_program(ROOM);
}
