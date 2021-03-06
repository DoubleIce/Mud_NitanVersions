inherit ROOM;

void create()
{
        set("short", "绿洲");
        set("long", @LONG
在沙漠的尽头出现了一个绿洲。这儿是南疆难得一见的草原。草
原上的夜晚，天很高、很蓝，星星很亮，青草和小花散播著芳香。隐
隐约约随风声飘来天铃鸟的歌声。这里居住着哈萨克人， 以放牧羊群
为生。灌木丛中有一眼坎儿井。井台上有个木杯专供口渴的行人喝水。
井边是一块瓜地。
LONG );
        set("outdoors", "gaochang");
        set("exits", ([
                "west" : __DIR__"huijiang3",
                "north" : __DIR__"huijiang7",
                "east" : __DIR__"lake4",
                "south" : __DIR__"lake5",
        ]));
        set("objects", ([
            	__DIR__"npc/su" : 1,
                "/clone/quarry/yang" : 2,
        ]));
        set("quarrys", ([
                "yang"  : 50000,
                "lang"  : 30000,
                "ying"  : 10000,
        ]));
        setup();
        replace_program(ROOM);
}
