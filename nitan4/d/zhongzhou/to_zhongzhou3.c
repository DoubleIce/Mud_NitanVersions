inherit ROOM;

void create()
{
	set("short", "中州道");
        set("long", @LONG
这条连接中州和扬州的要道来往车马不断。南面是中州城的北门，
再向北通向长江边的渡口。道路两边是一望无边的绿色沃野。好一片
江南风光。
LONG );
	set("no_clean_up", 0);
	set("exits", ([
  		"north" : __DIR__"to_zhongzhou2",
  		"south":__DIR__"beimen",
	]));
	set("outdoors", "zhongzhou");

	set("coor/x", -230);
	set("coor/y", 50);
	set("coor/z", 0);
	setup();
	replace_program(ROOM);
}
