// shiwudong.c
// Date: Nov.1997 by Venus
#include <room.h>
inherit ROOM;
void create()
{
        set("short", "石屋洞");
        set("long", @LONG
山路旁是石屋洞。石屋洞，洞中有洞，洞洞相连。主洞高大宽敞，
洁净明亮，上宽下窄，状如浮螺。西上便到了满觉陇；山路的尽头连
着一条由北至南的大道。
LONG );
        set("exits", ([
                "westup"    : "/d/hangzhou/manjuelong",
                "east"      : "/d/hangzhou/road18",
        ]));
	switch(random(1)){
	case 0:
                set("objects", ([ "/d/xingxiu/npc/scorpion" : 1,
                                  "/d/xingxiu/npc/spider" : 1,
                                  "/clone/worm/changaoxie": 1,
                                  "/d/xingxiu/npc/centipede" : 1,
				  "/d/xingxiu/npc/spider2" : 1]));
                break;
/*
        case 1:
                set("objects", ([ "/d/xingxiu/npc/spider" : 1]));
                break;
        case 2:
                set("objects", ([ "/d/xingxiu/npc/centipede" : 1]));
                break;
*/
        }
//        set("no_clean_up", 0);
        setup();
        replace_program(ROOM);
}

