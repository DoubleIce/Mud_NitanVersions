inherit ROOM;
void create()
{
	set("short", "昆仑山");
        set("long", @LONG
这茫茫山坡上一片白雪，四下并无行人，山势渐陡，雪积得厚厚
的，转过两个山坳，山道更是险峻。树木丛生，山石嶙峋，行走甚是
不便。
LONG );
	set("exits", ([ /* sizeof() == 2 */
                "eastup" : __DIR__"kunlun4",
                "northwest" : __DIR__"kunlun7",
]));
	set("no_new_clean_up", 0);
	set("outdoors", "kunlun");

	setup();
	replace_program(ROOM);
}
