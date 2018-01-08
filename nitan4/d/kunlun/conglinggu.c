inherit ROOM;

void create()
{
        set("short", "葱岭谷");
        set("long", @LONG
你的眼前突然为之一亮，只见一条象被一刀劈开的峡谷岩石间，
高山的雪水泻落到千丈以下的山涧里去，溅起的密密的飞沫激起一种
惊心动魄的震憾。就在这深山野谷的溪流边，却长满了各种各样的花
草树木，春天繁花开遍峡谷秋天果实压满山腰，人迹罕至，正是鸟兽
们的乐园。
LONG );
        set("exits",([
                "south" : __DIR__"shanlin" + (random(5) + 1),
        ]));

        set("objects", ([
                "/clone/herb/huangqi"   : random(2),
                "/clone/herb/chongcao"  : random(2),
                "/clone/herb/qianjinzi" : random(2),
                "/clone/herb/fuzi"      : random(2),
                "/clone/herb/renshen"   : random(2),
                "/clone/herb/mahuang"   : random(2),
        ]));

        setup();
        replace_program(ROOM);
}
