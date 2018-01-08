inherit ROOM;

void create()
{
	set("short", "沙砾小径");
        set("long", @LONG
这是一个无边的沙砾地，山势到了这里突然间变的无影无踪。地
气极干燥，连风都是暖的。地上的石砾发出一种暗红的颜色，就象是
被鲜血染红的一样。一条布满车痕的小径向西方和东方伸展。
LONG );
        set("outdoors", "gaochang");
	set("exits", ([
  		"west" : __DIR__"shamo2",
  		"eastup" : __DIR__"caoyuan7",
	]));
	setup();
	replace_program(ROOM);
}
