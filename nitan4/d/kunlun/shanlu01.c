inherit ROOM;

void create()
{
	set("short", "山路");
        set("long", @LONG
这里已经是昆仑派的地方了，路边花草满地，就算是寒冬季节，
这里却仍然生机勃勃，到处传来鸟兽的叫声，前面山上就是昆仑派的
居所了，北面是来的时候的山门。
LONG );
	set("exits",([
		"westdown" : __DIR__"shanmen",
		"southup" : __DIR__"shanlu02",
	]));

	set("outdoors", "昆仑");
	setup();
	replace_program(ROOM);
}
