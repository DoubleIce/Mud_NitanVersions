//room: chengdedian.c
inherit ROOM;

void create()
{
  set("short","成德殿");
        set("long", @LONG
这就是日月神教教主平日发号施令的地方，殿中无窗，殿口点着
明晃晃的蜡烛，大殿彼端高设一座，坐着一个英俊的中年人，自是名
震江湖的东方不败的姘头杨莲亭了！ 
LONG );

  set("valid_startroom", 1);
  set("exits",([
      "north" : "/d/heimuya/huoting",
      "westdown":"/d/heimuya/up4",
  ]));
  set("objects",([
      "/d/heimuya/npc/dizi" : 2,
      "/d/heimuya/npc/yang"    :1,
  ]));
//  set("no_clean_up", 0); 
  setup();
  replace_program(ROOM);
  "/clone/board/riyue_b"->foo();
}
