inherit ROOM;

void create()
{
        set("short", "小溪");
        set("long", @LONG
沙丘间忽然出现了稀稀落落的铁草，再奔一阵，地下青草渐多。
转眼之间，面前出现一条小溪，俯身溪边，掬了一口水喝下，只觉一
阵清凉，直透心肺。那水甘美之中还带有微微香气，想必出自一处绝
佳的泉水。溪水中无数小块碎冰互相撞击发出清脆声音，叮叮咚咚，
宛如仙乐。
LONG );
        set("outdoors", "gaochang");
        set("resource/water", 1);
        set("exits", ([ 
        	"north" : __DIR__"lake2",
        	"south" : __DIR__"lvzhou",
	]));
        setup();
}
