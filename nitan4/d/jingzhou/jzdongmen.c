inherit ROOM;

void create()
{
        set("short", "荆州东门" );
        set("long", @LONG
这里便是荆州西门，荆州历来都是军事要地，因此城墙坚实无比，
城楼高高耸立，来往的人很多，荆州也是从蜀地进入中原的必经之路，
所以各色人等混杂，你还是小心一点。东去则是通往扬州的交通要道。
LONG );
        set("objects", ([
                "/d/city/npc/bing" : 4,
                "/d/beijing/npc/ducha" : 1,
        ]));
        set("exits", ([
        	"east" : __DIR__"guandao3",
        	"west" : __DIR__"dongdajie2",
        ]));
        set("outdoors", "jingzhou");

        set("coor/x", -430);
	set("coor/y", -200);
	set("coor/z", 10);
	setup();
        replace_program(ROOM);
}

