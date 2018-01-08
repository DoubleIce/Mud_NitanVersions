inherit ROOM;

void create()
{
        set("short", "瑞鹤门");
        set("long", @LONG
这是通往天龙寺后寺的门户。你低头看看地上，只见铜门槛早已
被踩踏得锃亮，足见此寺香火之盛了。抬头向南可以望见点苍山耸立
云天。
LONG );
	set("outdoors","tianlongsi");
        set("exits", ([
		"south": __DIR__"wuchangge",
		"north": __DIR__"wuwoge",
	]));
        set("no_clean_up", 0);
        setup();
        replace_program(ROOM);
}
