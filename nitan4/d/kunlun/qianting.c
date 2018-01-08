inherit ROOM;

void create()
{
	set("short", "前厅");
        set("long", @LONG
这里是座大厅，高檐大瓦，十分的简朴壮阔，厅内摆几张高背方
椅，一张八仙桌，看来是接待客人的地方，西面和东面也是客厅，供
客人歇息，南面一条长廊通向后面。
LONG );
        set("exits",([
		"north" : __DIR__"pingfeng",
		"south" : __DIR__"shilu1",
		"west" : __DIR__"wlang01",
		"east" : __DIR__"elang01",
	]));

        set("objects",([
                CLASS_D("kunlun") + "/xihuazi" : 1,
        ]));

        set("no_clean_up", 0);
        setup();
}

int valid_leave(object me, string dir)
{
        object xi;

        if (dir != "south" ||
            ! objectp(xi = present("xi huazi", this_object())))
                return ::valid_leave(me, dir);

        return xi->permit_pass(me, dir);
}
