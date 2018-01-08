// Room: /d/suzhou/dangpu.c
// Date: May 31, 98  Java

inherit ROOM;

void create()
{
	set("short", "宝和记");
        set("long", @LONG
这是一家以买卖公平著称的当铺，一个五尺高的柜台挡在你的面
前，柜台上摆着一个牌子(sign)，柜台后坐着位老板，一双精明的眼
睛上上下下打量着你。
LONG );
	set("no_fight", 1);
	set("no_steal", 1);
	set("no_beg",1);
	set("no_clean_up", 0);
	set("exits", ([
		"north"  : "/d/suzhou/dongdajie1",
	]));
        set("item_desc", ([
                "paizi" : "公平交易\n
sell        卖 
buy         买
pawn        当
expiate     赎
value       估价
",
        ]));

	set("objects", ([
		"/d/suzhou/npc/wang" : 1,
	]));
	set("coor/x", 210);
	set("coor/y", -220);
	set("coor/z", 0);
	setup();
	replace_program(ROOM);
}

