inherit ROOM;

void create()
{
        set("short", "西郊");
        set("long", @LONG
这是中原第一府「中州府」的郊外。这儿离中州不远，治安也还
说得过去。西面是开封府方向，东边通向中州府。
LONG );
	set("exits", ([
  		"west" : __DIR__"wroad1",
  		"east" : __DIR__"chenglou",
	]));
	set("outdoors", "zhongzhou");
	set("no_clean_up", 0);

	set("coor/x", -280);
	set("coor/y", -10);
	set("coor/z", 0);
	setup();
	replace_program(ROOM);
}
