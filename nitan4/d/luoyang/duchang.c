inherit ROOM;

void create()
{
	set("short", "长乐坊");
        set("long", @LONG
在大门上挂者一块黑色的帘子，帘子上绣了个大大的『赌』字，
原来这里是一个赌场，就开在路边，好招摇呀！走进赌场，却发现里
面的布置如此繁华，热闹。金钱敲击之声不绝于耳，押注时的的吆喝
声充斥了每个人的耳朵，古语曰『十赌九输『，一旦踏进这里就难以
回头了，不输个倾家荡产，妻离子散你是不知道后悔的，只有少数几
个赢家才是赌徒们羡慕的对象和内心的希望。
LONG );
	set("no_clean_up", 0);
	set("exits", ([
  		"east" : __DIR__"sroad3",
	]));
        set("objects", ([
                "/d/kaifeng/npc/guanbing" : 1,
                "/d/city/npc/liumang" : 2,
                "/d/beijing/npc/haoke1" : 2,
                "/d/beijing/npc/duke" : 3,
                __DIR__"npc/dashou" : 1,
        ]));
	set("coor/x", -180);
	set("coor/y", 0);
	set("coor/z", 10);
	setup();
	replace_program(ROOM);
}
