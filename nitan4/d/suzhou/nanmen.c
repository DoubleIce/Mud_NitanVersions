// Room: /d/suzhou/nanmen.c
// Date: May 31, 98  Java

inherit ROOM;

string look_gaoshi();
void create()
{
	set("short", "南门");
        set("long", @LONG
这是苏州府的南城门。进进出出的吴侬软语，听来特让人舒服。
门口的官兵开口喝骂，也是这种软绵声气。门上贴着一份告示(gaosh
i)。南北一条笔直的官道。
LONG );
	set("outdoors", "suzhou");
	set("item_desc", ([
		"gaoshi" : (: look_gaoshi :),
	]));
	set("exits", ([
		"north" : "/d/suzhou/nandajie2",
		"south" : "/d/suzhou/road5",
	]));
        set("objects", ([
                "/d/city/npc/wujiang" : 1,
                "/d/city/npc/bing" : 2,
        ]));
	set("coor/x", 200);
	set("coor/y", -250);
	set("coor/z", 0);
	setup();
}

string look_gaoshi()
{
	return FINGER_D->get_killer() + "\n苏州知府\n冯正东\n";
}
