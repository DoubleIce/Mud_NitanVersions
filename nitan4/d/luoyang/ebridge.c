inherit ROOM;

void create()
{
	set("short", "城东桥");
        set("long", @LONG
此桥高跨洛阳护城河之上，气势非凡。站在桥上向两侧望去，一
条人工开掘的护城河将洛阳城围在当中，桥身以汉白玉造就，既美观
又很坚固。桥上车水马龙，川流不息。桥下的护城河水清澈见底，时
有游鱼跃起。
LONG );
        set("outdoors", "luoyang");
        set("no_clean_up", 0);
        set("exits", ([
  		"west" : __DIR__"dongdoor",
  		"eastdown" : __DIR__"guandaoe1",
	]));

	set("coor/x", -100);
	set("coor/y", 0);
	set("coor/z", 10);
	setup();
	replace_program(ROOM);
}
