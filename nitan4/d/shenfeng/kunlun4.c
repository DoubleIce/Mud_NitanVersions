inherit ROOM;

void create()
{
	set("short", "昆仑山");
        set("long", @LONG
这座松林好长，走了半个时辰方始过完，一出松林，只见眼前满
峰是雪，使人更觉惊心动魄。银色的月光映著银色的雪，身当此境，
不禁也生栗栗之感，顿觉大千无限，一己渺小异常。
LONG );
	set("no_new_clean_up", 0);
	set("outdoors", "kunlun");

	set("exits", ([ /* sizeof() == 3 */
                "westdown" : __DIR__"kunlun6",
                "south" : __DIR__"kunlun5",
                "eastdown" : __DIR__"kunlun3",
        ]));

	setup();
	replace_program(ROOM);
}
