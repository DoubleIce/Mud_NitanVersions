inherit ROOM;

void create()
{
	set("short", "居室");
        set("long", @LONG
一间颇为精致的小屋，似乎是女子的居所。房间的中央摆着一支
香炉，缓缓散发着清香。门前还悬挂着一笼白鹦鹉，雕花檀香木的床
上整齐的叠放着锦缎绸被。
LONG );
	set("exits", ([
  		"south" : __DIR__"miaojia_zoulang1",
	]));
	set("no_clean_up", 0);
        set("objects", ([
                CLASS_D("miao") + "/lan" : 1,
        ]));
	set("coor/x", -190);
	set("coor/y", 40);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}
