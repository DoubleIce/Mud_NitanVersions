//room: 
inherit ROOM;

void create()
{
  set("short","长廊");
        set("long", @LONG
这里是非常气派的长廊。但是却没什么人在这里，南边是青龙堂
的大厅。
LONG );

  set("exits",([
      "north" : "/d/heimuya/chlang1",
      "south" : "/d/heimuya/qing",
  ]));			   
  set("objects",([
      "/d/heimuya/npc/shinu1"   :1,
  ]));
  set("no_fight",0);
  set("no_steal",0);
  set("no_clean_up", 0);
  setup();
  replace_program(ROOM);
}

