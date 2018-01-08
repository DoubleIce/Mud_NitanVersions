inherit ROOM;

void create()
{
        set("short", "开封铁塔");
        set("long", @LONG
塔高五十五米，八角十三层。当年此地为宋开宝寺，故又名『开
宝寺塔』，塔身为褐色琉璃砖砌成混私铁铸，民间俗称其为铁塔。塔
身修长，气势雄伟，砖面饰以飞天、佛像、乐伎等数十种图案，栩栩
如生。
LONG );
        set("outdoors", "kaifeng");
        set("exits", ([
		"west" : __DIR__"jieying",
		"east" : __DIR__"eroad3",
	]));
        set("objects", ([
        ]));
        set("no_clean_up", 0);
        setup();
        replace_program(ROOM);
}
