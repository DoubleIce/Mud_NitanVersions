// ROOM : lianxin.c
inherit ROOM;
void create()
{
  set("short","涟星宫");
        set("long", @LONG
这是邀月宫主休息的地方，只见一个身材奇好，貌美如花的女子
站立在花丛中，她就是武功奇高，身份神秘的移花宫大宫主。以前因
为她的姐姐邀月宫主被燕南天抛弃所以她非常恨男人，如果你是男人
最好不要接近她。
LONG );
  set("exits",([
      "east" : __DIR__"changlang1",
      "southeast" : __DIR__"woshi",
     ]));
  set("objects",([
        //__DIR__"npc/lianxing" : 1,
     ]));
 setup();
 replace_program(ROOM);
}
