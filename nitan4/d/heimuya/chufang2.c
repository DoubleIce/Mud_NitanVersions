//chufang1.c
inherit ROOM;
void create()
{
  set("short","厨房");
        set("long", @LONG
这是白虎堂的厨房，一位美丽侍女满脸堆笑。整个房间菜香胭脂
香迷漫。墙上贴着一张醒目的启事(note)。
LONG );
  set("exits",([
      "west" : "/d/heimuya/chitang",
  ]));
  set("item_desc",([
      "note" : "最难消受女人福，红颜祸水。----->岳不群题\n",
  ]));

  set("objects",([
      "/d/heimuya/npc/shinu" : 1,
      "/d/heimuya/obj/tea" : random(6),
      "/d/heimuya/obj/sherou"  : random(4),
  ]));
//  set("no_clean_up", 0);
  setup();
}
int valid_leave(object me, string dir)
{
	if (( present("tea", me)||present("she rou", me))
	&&objectp(present("shi nu", environment(me))) )
	return notify_fail
	("侍女美目一挑，想走，没门！\n");
	return ::valid_leave(me, dir);
}

