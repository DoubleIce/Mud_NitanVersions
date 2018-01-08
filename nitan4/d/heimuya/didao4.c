//room: didao4.c
inherit ROOM;

void create()
{
  set("short","秘道尽头");
        set("long", @LONG
你忽觉前方有一亮光，真是别有洞天，前方好像别有地方。
LONG );
  set("exits",([
      "east"   :"/d/heimuya/didao1",
      "west"  :"/d/heimuya/didao3",
      "south" : "/d/heimuya/didao4",
      "southup" : "/d/heimuya/didao6",
  ]));
  set("no_clean_up", 0);
  setup();
  replace_program(ROOM);
}
