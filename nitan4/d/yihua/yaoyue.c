// ROOM : yaoyue.c
inherit ROOM;
void create()
{
  set("short","邀月宫");
        set("long", @LONG
这是邀月宫主休息的地方，只见一个身材奇好， 貌美如花的女子
站立在花丛中，她就是武功奇高，身份神秘的移花宫大宫主。以前因
为被燕南天抛弃所以她非常恨男人，如果你是男人最好不要接近她。
LONG );
  set("exits",([
      "west" : __DIR__"changlang1",
      "southwest" : __DIR__"woshi",
     ]));
  set("objects",([
        //__DIR__"npc/yaoyue" : 1,
     ]));
 setup();
 replace_program(ROOM);
}
