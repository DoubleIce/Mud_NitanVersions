inherit ROOM;

void create()
{
        set("short", "大观园茶楼");
        set("long", @LONG
大观园茶楼乃中州城内屈指可数的大茶楼，可是茶楼里却没几个
人。里面好象有个楼梯往下，微微从下面透出的味道让人闻了头有点
发昏。
LONG );
        set("exits", ([
  		"east" : __DIR__"wendingnan2",
  		"down" : __DIR__"yanguan",
	]));
        set("no_clean_up", 0);

        set("coor/x", -240);
	set("coor/y", -30);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}
