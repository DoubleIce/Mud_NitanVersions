inherit ROOM;

void create()
{
	set("short", "淳熙路");
        set("long", @LONG
淳熙大路是洛阳最整洁的一条大路，街道宽敞而干净，汉白玉砌
的路面被雨水冲得光明如镜，大路两侧的瓦房高大而宏伟，分明便是
巨富宅院。双人合抱的杨树十步一株，整齐的排在两边。西边是一家
皮货店，东边是一条青石小巷，笔直通往一座新建兰薪寺 。
LONG );
        set("outdoors", "luoyang");
	set("exits", ([
  		"east" : __DIR__"xiaoxiang",
  		"north" : __DIR__"beidoor",
  		"south" : __DIR__"nroad3",
  		"west" : __DIR__"pimao",
	]));
        set("objects", ([
                "/d/beijing/npc/xianren" : 1,
        ]));
	set("coor/x", -170);
	set("coor/y", 40);
	set("coor/z", 10);
	setup();
	replace_program(ROOM);
}
