// Room: /d/suzhou/zijinan.c
// Date: May 31, 98  Java

inherit ROOM;

void create()
{
	set("short", "紫金庵");
        set("long", @LONG
这是一座苏州城里有名的寺庵，庵中正面是释加摩尼佛眼，似乎
在注视前来礼佛之人；右壁一尊诸天用三个手指托起一块轻柔的绣花
经盖和后壁观音菩萨头上的一顶刻着牡丹花的紫红色华盖。左壁的每
尊罗汉塑像造型生动，各具特征，到达了以神人话、精神超忽、呼之
欲活的艺术境界，令人叹为观止。
LONG );
	set("objects", ([
		"/d/suzhou/obj/box" : 1,
		"/d/suzhou/npc/nigu1" : 1,
		"/d/suzhou/npc/nigu2" : 1,
	]));
	set("outdoors", "suzhou");
	set("no_clean_up", 0);
	set("exits", ([
		"east"      : "/d/suzhou/beidajie2",
	]));
	set("coor/x", 190);
	set("coor/y", -180);
	set("coor/z", 0);
	setup();
	replace_program(ROOM);
}

