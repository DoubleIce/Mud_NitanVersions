#include <ansi.h>
#include <room.h>
inherit RIVER;

void create()
{
        set("short", "大门坎子");
        set("long", @LONG
这里是沿江向东的古道，多为进山采参的参客所走，因此也称参
路。前面一座小山截断去路，为东去采参的第一道屏障故被称为大门
坎子。西面是宽阔的松花江 (river)。松花江在冬春时结冰可以通行，
夏秋化冻你只好找船家帮忙了。
LONG );
        set("arrive_room", "/d/guanwai/chuanchang");
        set("exits", ([
                "southeast"  : __DIR__"ermenkan",
        ]));
        set("resource/fish", ({ "/clone/fish/liyu",
                                "/clone/fish/jiyu",
                                "/clone/fish/qingyu",
                                "/clone/fish/caoyu", }));

        set("outdoors", "guanwai");
        setup();
        replace_program(RIVER);
}
