// Room: /u/mei/room54.c// This is a room made by roommaker. write by Fan. :)
inherit ROOM;
void create()
{
	set("short", "昆仑山");
        set("long", @LONG
山势在这里渐渐升高，周围的景象在浓雾中若隐若现。浓雾中的
水气几乎浸透了你的衣裳，将你溶入冰冷的四周。这…到底是人间通
往天堂的路，还是通往地狱之门？
LONG );
	set("exits", ([ /* sizeof() == 2 */
                "southup" : __DIR__"kunlun3",
                "eastdown" : __DIR__"kunlun1",
                "enter" : "/d/llszhuang/road",
]));
	set("no_new_clean_up", 0);
	set("outdoors", "kunlun");

	setup();
	replace_program(ROOM);
}
