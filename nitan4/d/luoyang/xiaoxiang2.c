inherit ROOM;

void create()
{
	set("short", "青石小巷");
        set("long", @LONG
这里一条青石小路，路面用青石板铺成，刚刚下过雨，路面很是
干净，小巷内静悄悄的，只能听见自己的脚步声，偶尔风吹动树枝发
出沙沙的响声。
LONG );
        set("outdoors", "luoyang");
        set("no_clean_up", 0);
        set("exits", ([
  		"east" : __DIR__"juyi",
  		"west" : __DIR__"xiaoxiang",
	]));
        set("objects", ([
                "/d/beijing/npc/kid1" : 1,
        ]));

	set("coor/x", -150);
	set("coor/y", 40);
	set("coor/z", 10);
	setup();
	replace_program(ROOM);
}
