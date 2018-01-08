inherit ROOM;

void create()
{
	set("short", "星星峡");
        set("long", @LONG
远处出现了一抹岗峦。转眼之间，石壁越来越近，一字排开，直
伸出去，山石间云雾瀰漫，似乎其中别有天地，再走近时忽觉峭壁中
间露出一条缝来，沿山道直走进去，便是甘肃和回疆之间的交通孔道
星星峡。
LONG );
        set("outdoors", "gaochang");
	set("exits", ([
  		"west" : __DIR__"xingxing2",
  		"east" : __DIR__"guandao4",
	]));
        set("objects", ([
                __DIR__"npc/seller" : 1,
        ]));
	setup();
	replace_program(ROOM);
}
