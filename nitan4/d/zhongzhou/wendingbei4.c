inherit ROOM;

void create()
{
	set("short", "文定北街");
        set("long", @LONG
这是中州城文定北街，这里离中州北城门已不远。街上冷冷清清
没几个人影。街道的东面有一座深宅大院。门口挂着的匾上赫然刻着
苗家庄三个大字。西面是一长条的平房。
LONG );
	set("exits", ([
  		"south" : __DIR__"wendingbei3",
  		"east"  : __DIR__"miaojia_men",
  		"west"  : __DIR__"congwu",
  		"north" : __DIR__"beimen",
	]));

	set("no_clean_up", 0);
	set("outdoors", "zhongzhou");
	set("objects", ([
  		"/d/beijing/npc/tangzi" : 1,
	]));

	set("coor/x", -230);
	set("coor/y", 30);
	set("coor/z", 0);
	setup();
	replace_program(ROOM);
}
