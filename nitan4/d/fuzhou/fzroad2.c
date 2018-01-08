inherit ROOM;

void create()
{
	set("short", "武夷山道");
        set("long", @LONG
你走在窄窄的武夷山小道上，山路崎岖，密林森森，常有长虫野
兽出没。所谓「闽道更比蜀道难」诚不相欺。西面隔着崇阳溪，就是
奇秀甲于东南的武夷山了。
LONG );
	set("exits", ([
		"northup" : __DIR__"erbapu",
		"southup" : __DIR__"fzroad3",
		"west"    : __DIR__"wuyishan1",
	]));
	set("outdoors", "fuzhou");
	set("coor/x", 80);
	set("coor/y", -70);
	set("coor/z", 0);
	setup();
	replace_program(ROOM);
}

