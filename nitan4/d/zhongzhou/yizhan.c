inherit ROOM;

void create()
{
        set("short", "驿站");
        set("long", @LONG
这里是中州城的驿站，这个驿站不大，一边是个小小的草蓬，几
个官差在此落脚。
LONG );

        set("no_clean_up", 0);
        set("exits", ([
  		"west" : __DIR__"wendingnan4",
	]));

        set("coor/x", -220);
	set("coor/y", -50);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}
