// yanxiadong.c
// Date: Nov.1997 by Venus
#include <room.h>
inherit ROOM;
void create()
{
        set("short", "烟霞洞");
        set("long", @LONG
据说站在山头，清晨观看山村缭绕炊烟，傍晚仰望蓝天彩霞，景
色优美，故称『烟霞』。洞口两旁有精美的『观音』和『大势至菩萨
』洞内两壁的天然岩穴里有各代的石刻。往东是下山的路。西边是去
龙井。
LONG );
        set("exits", ([
                "west"     : "/d/hangzhou/shanlu5",
                "eastdown" : "/d/hangzhou/shuiledong",
        ]));
        set("no_clean_up", 0);
        setup();
        replace_program(ROOM);
}
