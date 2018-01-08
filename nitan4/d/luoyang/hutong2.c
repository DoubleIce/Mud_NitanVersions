inherit ROOM;

void create()
{
	set("short", "小胡同");
        set("long", @LONG
这里是洛阳城内老百姓的居住区。胡同内很安静，没有什么杂声。
一些居民从这里进进出出。越往胡同里走，一些全身穿着白色长衣的
人就越多了，只见这些人鬼鬼祟祟，眼神恍惚，行踪可疑，让人猜不
透是干什么的。
LONG );
        set("outdoors", "luoyang");
        set("no_clean_up", 0);
        set("exits", ([
  		"south" : __DIR__"hutong",
  		"north" : __DIR__"hutong3",
  		"west" : __DIR__"wanju",
	]));

	set("coor/x", -120);
	set("coor/y", 20);
	set("coor/z", 10);
	setup();
	replace_program(ROOM);
}
