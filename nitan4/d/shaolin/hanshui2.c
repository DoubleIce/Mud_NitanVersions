#include <ansi.h>
#include <room.h>
inherit RIVER;

void create()
{
        set("short", "汉水北岸");
        set("long", @LONG
汉水北岸也是相当热闹，自北岸渡口往北，一条笔直的官道直通
南阳。此地民风淳朴，路旁夹柳成阴酒厮林立，且都有面大大的「酒
」旗迎风飘扬，蔚为壮观。也有不少小贩沿路叫买，语多难辨，却也
令人盛情难却。
LONG );
        set("arrive_room", "/d/shaolin/hanshui1");
        set("exits", ([
                "north" : __DIR__"nanyang",
        ]));

        set("resource/fish", ({ "/clone/fish/liyu",
                                "/clone/fish/jiyu",
                                "/clone/fish/qingyu",
                                "/clone/fish/caoyu", }));

        set("objects", ([
                __DIR__"npc/chuanfu1" : 1,
        ]));

        set("outdoors", "nanyang");
        set("coor/x", 0);
	set("coor/y", 100);
	set("coor/z", 0);
	setup();
        replace_program(RIVER);
}
