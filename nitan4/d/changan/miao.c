//Room: miao.c

inherit ROOM;

void create ()
{
        set ("short", "城隍庙");
        set("long", @LONG
庙有一大半倾塌了，本来就不大，现在就显得更小了，不过小无
减于它的慑人气氛。没有倾塌的是神殿的一角，而且刚好是神像所在
的地方，所以那尊土塑的山神还算是完好的。这也不知是比照哪一位
尊神所塑的像？青面獠牙，眼睛瞪得像两枚铜铃，而且还熠熠发光。
LONG );
        set("exits", ([
        	"west"   : "/d/changan/yongtai-dadao4",
        ]));
        set("objects", ([
        	"/d/changan/npc/keeper"   : 1,
        ]));

        set("no_fight",1);
        set("coor/x", -430);
	set("coor/y", -10);
	set("coor/z", 0);
	setup();
}
