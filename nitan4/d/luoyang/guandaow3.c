inherit ROOM;

void create()
{
	set("short", "大官道");
        set("long", @LONG
这是一条宽阔笔直，尘土飞扬的大官道，它连接了东都长安和西
都洛阳。官道很是宽广，足可容得下十马并驰。往西直达长安的东门，
而东边则是洛阳古城。
LONG );
        set("outdoors", "luoyang");
        set("no_clean_up", 0);
        set("exits", ([
  		"east" : __DIR__"guandaow2",
  		"west" : __DIR__"guandaow4",
	]));

	set("coor/x", -270);
	set("coor/y", 0);
	set("coor/z", 0);
	setup();
	replace_program(ROOM);
}
