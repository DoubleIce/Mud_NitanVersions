inherit ROOM;

void create()
{
        set("short", "药铺");
        set("long", @LONG
这是中州城最大的药铺。从普通药材到名贵的中草药一应俱全。
浓浓的药味让你有点透不过气来。店里人来人往的，看的出此处生意
不错。你如需要药的话可以向小二买一点，如你有药方后院还可以让
你自己熬药。
LONG );
        set("objects", ([
  		"/d/city/npc/huoji" : 1,
	]));

        set("no_clean_up", 0);
        set("exits", ([
  		"north" : __DIR__"yaopuboss",
  		"west" : __DIR__"wendingbei2",
  		"south" : __DIR__"yaopu1",
	]));

        set("coor/x", -220);
	set("coor/y", 10);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}
